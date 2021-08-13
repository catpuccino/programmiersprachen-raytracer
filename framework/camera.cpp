#include "camera.hpp"
#include <glm/gtx/intersect.hpp>


Camera::Camera(float angle, const glm::vec3 &origin, const glm::vec3 &direction) :
  fov_x_{angle},
  origin_{origin},
  direction_{direction} {}

Camera::~Camera() {}

Ray Camera::compute_eye_ray(float pix_x, float pix_y, unsigned width) const {
  int distance = 1 / tan(fov_x_ / 2);
  
  glm::vec3 pixel_3DPoint{ pix_x, pix_y, -distance };
  glm::vec3 eye_ray_dir = glm::normalize(pixel_3DPoint - origin_);
  return Ray{ origin_, eye_ray_dir };
}

