// -----------------------------------------------------------------------------
// Copyright  : (C) 2014-2017 Andreas-C. Bernstein
// License    : MIT (see the file LICENSE)
// Maintainer : Andreas-C. Bernstein <andreas.bernstein@uni-weimar.de>
// Stability  : experimental
//
// Renderer
// -----------------------------------------------------------------------------

#include "renderer.hpp"
#include <algorithm>

Renderer::Renderer(unsigned w, unsigned h, std::string const& file, Scene const& s)
  : width_(w)
  , height_(h)
  , color_buffer_(w*h, Color{0.0, 0.0, 0.0})
  , filename_(file)
  , ppm_(width_, height_)
  , scene_(s)
{}

void Renderer::render()
{
  float distance = scene_.camera.compute_screen_distance(width_);

  for (unsigned y = 0; y < height_; ++y) {
    for (unsigned x = 0; x < width_; ++x) {

      Pixel p(x,y);

      Ray current_eye_ray = scene_.camera.compute_eye_ray((float)x - ((float)width_ / 2),
                                                          (float)y - ((float)height_/ 2),
                                                          distance);

      p.color = trace_ray(current_eye_ray, 0);
      write(p);
    }
  }
  ppm_.save(filename_);
}

void Renderer::write(Pixel const& p)
{
  // flip pixels, because of opengl glDrawPixels
  size_t buf_pos = (width_*p.y + p.x);
  if (buf_pos >= color_buffer_.size() || (int)buf_pos < 0) {
    std::cerr << "Fatal Error Renderer::write(Pixel p) : "
      << "pixel out of ppm_ : "
      << (int)p.x << "," << (int)p.y
      << std::endl;
  } else {
    color_buffer_[buf_pos] = p.color;
  }

  ppm_.write(p);
}

Color Renderer::shade(Shape const& obj, Ray const& ray, HitPoint const& hp, unsigned recursionDepth) const {
  // intersection point (fundament of illumination)
  glm::vec3 intersect_point = hp.hitpoint;


  // ********* (PHONG) ILLUMINATION **********

  // vectors (independent of lights)
  glm::vec3 n = obj.create_normal(hp); // normal vector on intersection point
  glm::vec3 v = glm::normalize(ray.origin - intersect_point); // vector to the viewer (camera)


  intersect_point += 0.001f * n; /* add little offset to intersection point to prevent shape from
                                     intersecting with itself (shadow acne) */


  // *** ambient component ***
  auto ambient_intensity = scene_.ambient * hp.material->ka;


  // *** diffuse and specular components depending on num of impacting lights ***
  Color diffuse_intensity = {0.0f, 0.0f, 0.0f};
  Color specular_intensity = { 0.0f, 0.0f, 0.0f };

  for (auto const& [l_name,light_o] : scene_.light_cont) {
    glm::vec3 l = glm::normalize(light_o->position - intersect_point); // create light vector

    // initialize secondary ray between intersection point and light
    Ray sec_ray{intersect_point,l};

    // test whether this specific light contributes to illumination
    bool isIntersecting = false;
    for (auto const& [s_name,shape_o] : scene_.shape_cont) {
      // test if some scene obj gets intersected by sec_ray
      HitPoint sec_ray_hp = shape_o->intersect(sec_ray);
      if (sec_ray_hp.did_intersect) { isIntersecting = true; }
    }
    if (isIntersecting) { continue; }
    // else (Light has an impact)

    // compute diffuse intensity contributed by this specific light
    auto frac_diffuse_intensity = light_o->brightness * hp.material->kd * std::max(glm::dot(l,n),0.0f);
    diffuse_intensity += frac_diffuse_intensity;

    // compute specular intensity contributed by this specific light
    glm::vec3 r = glm::normalize(2 * std::max(glm::dot(l,n),0.0f) * n - l); // reflected light vector
    float dot_r_v = std::max(glm::dot(r,v),0.0f);
    auto frac_specular_intensity = hp.material->ks * pow(dot_r_v,hp.material->m);
    specular_intensity += frac_specular_intensity;
    }

  Color c_hdr = ambient_intensity + diffuse_intensity + specular_intensity; // High Dynamic Range
  Color c_ldr = c_hdr / (c_hdr + 1); // Low Dynamic Range

  if (hp.material->reflection > 0.0f && recursionDepth < 10) {
    // generate and trace reflected ray (reflected on normal)
    glm::vec3 reflected_vec = glm::normalize(
            hp.hit_direction - 2 * glm::dot(hp.hit_direction,n) * n);
    Ray reflected_ray = {intersect_point,reflected_vec};
    c_ldr = (1 - hp.material->reflection) * c_ldr +
            hp.material->reflection * trace_ray(reflected_ray, recursionDepth + 1);
  }

  return c_ldr;
  }


Color Renderer::trace_ray(Ray const& ray, unsigned recursionDepth) const {
    HitPoint temp_hp;
    HitPoint closest_hp;
    std::shared_ptr<Shape> closest_shape;
    float smallest_distance = std::numeric_limits<float>::infinity();

    for (auto const& [s_name,shape] : scene_.shape_cont) {
        temp_hp = shape->intersect(ray);
        if (temp_hp.did_intersect && temp_hp.distance < smallest_distance) {
            smallest_distance = temp_hp.distance;
            closest_hp = temp_hp;
            closest_shape = shape;
        }
    }

    if (smallest_distance != std::numeric_limits<float>::infinity()) {
        return shade(*closest_shape,ray,closest_hp, recursionDepth);
    }
    else {
        return scene_.background_color;
    }
}
