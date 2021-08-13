#include "camera.hpp"
#include <glm/gtx/intersect.hpp>


Camera::Camera(float angle, const glm::vec3 &origin, const glm::vec3 &direction) :
  fov_x_{angle},
  origin_{origin},
  direction_{direction} {}

Camera::~Camera() {}

Ray Camera::compute_eye_ray(float x, float y, unsigned width) const {
  int distance = (width / 2) / tan(fov_x_ * M_PI / 180);
  distance = 4;
  glm::vec3 pixel_3DPoint{x, y, -1*distance };
  glm::vec3 eye_ray_dir = glm::normalize(pixel_3DPoint - origin_);
  return Ray{ origin_, eye_ray_dir };

}

