// -----------------------------------------------------------------------------
// Copyright  : (C) 2014-2017 Andreas-C. Bernstein
// License    : MIT (see the file LICENSE)
// Maintainer : Andreas-C. Bernstein <andreas.bernstein@uni-weimar.de>
// Stability  : experimental
//
// Renderer
// -----------------------------------------------------------------------------

#include "renderer.hpp"

Renderer::Renderer(unsigned w, unsigned h, std::string const& file)
  : width_(w)
  , height_(h)
  , color_buffer_(w*h, Color{0.0, 0.0, 0.0})
  , filename_(file)
  , ppm_(width_, height_)
{}

void Renderer::render()
{
  std::size_t const checker_pattern_size = 20;

  for (unsigned y = 0; y < height_; ++y) {
    for (unsigned x = 0; x < width_; ++x) {
      Pixel p(x,y);
      if ( ((x/checker_pattern_size)%2) != ((y/checker_pattern_size)%2)) {
        p.color = Color{0.0f, 1.0f, float(x)/height_};
      } else {
        p.color = Color{1.0f, 0.0f, float(y)/width_};
      }

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


Color Renderer::trace_ray(Ray const& ray, Scene const& scene) const {
    HitPoint temp_hp;
    HitPoint closest_hp;
    std::pair<std::string, std::shared_ptr<Shape>> closest_shape;
    float smallest_distance = std::numeric_limits<float>::infinity();

    for (auto const& shape : scene.shape_cont) {
        temp_hp = shape.second->intersect(ray);
        if (temp_hp.did_intersect && temp_hp.distance < smallest_distance) {
            smallest_distance = temp_hp.distance;
            closest_hp = temp_hp;
            closest_shape = shape;
        }
    }

    if (smallest_distance != std::numeric_limits<float>::infinity()) {
        // insert function call shade(closest_shade, ray, closest_hp) here
        return Color{ 0.5f, 0.5f, 0.5f };  
    }
    else {
        return scene.background_color;
    }
}
