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

  // compute transformation matrix to fit to camera position
  glm::mat3x4 camera_transform = scene_.camera.compute_camera_transform_matrix();

  for (unsigned y = 0; y < height_; ++y) {
    for (unsigned x = 0; x < width_; ++x) {

      Pixel p(x,y);

      Ray current_eye_ray = scene_.camera.compute_eye_ray((float)x - ((float)width_ / 2),
                                                          (float)y - ((float)height_/ 2),
                                                          distance, camera_transform);

      p.color = trace_ray(current_eye_ray);
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

Color Renderer::shade(Shape const& obj, Ray const& ray, HitPoint const& hp) const {
  // intersection point (fundament of illumination)
  glm::vec3 intersect_point = hp.hitpoint;


  // ********* (PHONG) ILLUMINATION **********

  // vectors (independent of lights)
  glm::vec3 n = hp.normal; // normal vector on intersection point
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

    // calculate distance from Hitpoint to lightsource
    auto hp_light_distance = glm::distance(light_o->position, intersect_point);
    // initialize secondary ray between intersection point and light
    Ray sec_ray{intersect_point,l};

    // test whether this specific light contributes to illumination
    bool isIntersecting = false;
    bool isTransparent = false;
    std::vector<float> opacities;
    for (auto const& [s_name,shape_o] : scene_.shape_cont) {
      // test if some scene obj gets intersected by sec_ray

      // transform ray to object-space
      Ray os_sec_ray = shape_o->transformRay(sec_ray); // object-space second-ray
      HitPoint os_sec_ray_hp = shape_o->intersect(os_sec_ray);
      // calculate hitpoint in world-space
      HitPoint sec_ray_hp = shape_o->transform_objSpace_hp_to_wrldSpace(os_sec_ray_hp);
      
      // checks if intersected shape is located behind light source
      if (sec_ray_hp.distance > hp_light_distance) { continue; }

      if (sec_ray_hp.did_intersect) {
          /* checks if second ray accidentally intersects with the shape it belongs to
          (problem since object-space intersection test) */
          if (sec_ray_hp.name == s_name) { continue; }

          isIntersecting = true; 
          if (sec_ray_hp.material->opacity < 1.0f) {
              isTransparent = true;
              opacities.push_back(sec_ray_hp.material->opacity);
          }
      }
    }
    
    // if intersected object is transparent, shadow is adjusted accordingly
    if (isIntersecting && isTransparent) { 

        // compute diffuse intensity contributed by this specific light, dependent on shadow
        auto frac_diffuse_intensity = light_o->brightness * hp.material->kd * std::max(glm::dot(l, n), 0.0f);
        for (auto obj : opacities) {
            frac_diffuse_intensity = (1 - obj) * frac_diffuse_intensity;
        }
        diffuse_intensity += frac_diffuse_intensity;

        // compute specular intensity contributed by this specific light, dependent on shadow
        glm::vec3 r = glm::normalize(2 * std::max(glm::dot(l, n), 0.0f) * n - l); // reflected light vector
        float dot_r_v = std::max(glm::dot(r, v), 0.0f);
        auto frac_specular_intensity = hp.material->ks * pow(dot_r_v, hp.material->m);
        for (auto obj : opacities) {
            frac_specular_intensity = (1 - obj) * frac_specular_intensity;
        }
        specular_intensity += frac_specular_intensity;
        
    }
    
    else if (isIntersecting) { continue; }

    // else (Light has an impact)
    else {

        // compute diffuse intensity contributed by this specific light
        auto frac_diffuse_intensity = light_o->brightness * hp.material->kd * std::max(glm::dot(l, n), 0.0f);
        diffuse_intensity += frac_diffuse_intensity;

        // compute specular intensity contributed by this specific light
        glm::vec3 r = glm::normalize(2 * std::max(glm::dot(l, n), 0.0f) * n - l); // reflected light vector
        float dot_r_v = std::max(glm::dot(r, v), 0.0f);
        auto frac_specular_intensity = hp.material->ks * pow(dot_r_v, hp.material->m);
        specular_intensity += frac_specular_intensity;
    }
  }

  Color c_hdr = ambient_intensity + diffuse_intensity + specular_intensity; // high dynamic range
  
  if (hp.material->reflection > 0.0f) {
      c_hdr = (1 - hp.material->reflection) * c_hdr + hp.material->reflection * reflect(ray, hp, n);
  }


  // if object is transparent, calculates refracted part of the color
  if (hp.material->opacity < 1.0f) {
      
      // adds together regular color and refracted part, depending on opacity of object
      c_hdr = hp.material->opacity * c_hdr + (1.0f - hp.material->opacity) * refract(ray, hp, n);
  }

  Color c_ldr = c_hdr / (c_hdr + 1); // Low Dynamic Range

  return c_ldr;
  }
 
 Color Renderer::reflect(Ray const& ray, HitPoint const& hp, glm::vec3 const& normal) const  {
      if (ray.counter < 10) {
          auto intersection_point = hp.hitpoint + 0.001f * normal;
          auto reflect_ray_direction = ray.direction - 2 * glm::dot(normal, ray.direction) * normal;
          Ray reflect_ray{ intersection_point, reflect_ray_direction, 1.0f, ray.counter + 1 };
          return trace_ray(reflect_ray);  
      }
      else {
          return scene_.background_color;
      }
  }

// method to compute refract ray, doesn't allow for intersecting objects
Color Renderer::refract(Ray const& ray, HitPoint const& hp, glm::vec3 const& normal) const {
    
    // checks depth of recursion
    if (ray.counter < 10) {

        // initialize variables
        auto intersection_point = hp.hitpoint;
        auto ray_refract_index = ray.current_refraction_index;
        auto hp_refract_index = hp.material->refraction_index;
        auto I = ray.direction; // directional vector of ray
        auto N = normal;
        auto N_dot_I = glm::dot(N, I); // angle between normal and ray
        glm::vec3 refract_direction; // direction of refracted ray

        // ray comes from inside the object:
        if (N_dot_I > 0) {

            // reverse normal, so that it points inwards
            N = { normal.x * -1, normal.y * -1, normal.z * -1 };
            
            // swap material refract indexes of ray and material
            std::swap(ray_refract_index, hp_refract_index);

            // add offset to intersection point to prevent acne
            intersection_point += 0.001f * normal;
        }

        // ray comes from outside the object
        else {

            // subtract offset from intersection point to prevent acne
            intersection_point -= 0.001f * normal;

            // N-dot_i is smaller than 0, reverse sign to ensure it's positive
            N_dot_I = -N_dot_I;
        }

        // calculate relation between refract index of material that's left and material that's entered
        float relative_refract_index = ray_refract_index / hp_refract_index;

        auto k = 1.0f - pow(relative_refract_index, 2) * (1.0f - pow(N_dot_I, 2));
        // if critical angle is reached, -> total internal reflection -> no refraction occurs
        if (k < 0.0f) {
            refract_direction = { 0.0f, 0.0f, 0.0f };
        }
        // else, calculate direction of refracted ray
        else {
            refract_direction =
                relative_refract_index * I + float((relative_refract_index * N_dot_I - sqrt(k))) * N;
        }

        // initialize refraction ray with refraction index == 1.0f (air)
        Ray refraction_ray = { intersection_point, refract_direction, 1.0f, ray.counter + 1 };

        // trace refraction ray
        return trace_ray(refraction_ray);
    }

    // if recursion limit is reached, return background color
    else {
        return scene_.background_color;
    }
}

Color Renderer::trace_ray(Ray const& ray) const {
    HitPoint temp_hp;
    HitPoint closest_hp;
    std::shared_ptr<Shape> closest_shape;
    float smallest_distance = std::numeric_limits<float>::infinity();


    for (auto const& [s_name,shape] : scene_.shape_cont) {
        // transform ray to object-space
        Ray os_ray = shape->transformRay(ray); // object-space ray

        HitPoint os_temp_hp = shape->intersect(os_ray); // object-space temporary hitpoint

        if (os_temp_hp.did_intersect && os_temp_hp.distance < smallest_distance) {
            // calculate hitpoint in world-space
            temp_hp = shape->transform_objSpace_hp_to_wrldSpace(os_temp_hp);

            smallest_distance = temp_hp.distance;
            closest_hp = temp_hp;
            closest_shape = shape;
        }
    }

    if (smallest_distance != std::numeric_limits<float>::infinity()) {
        return shade(*closest_shape,ray,closest_hp);
    }
    else {
        return scene_.background_color;
    }
}
