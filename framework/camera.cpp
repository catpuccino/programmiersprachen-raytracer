#include "camera.hpp"
#include <glm/gtx/intersect.hpp>


Camera::Camera(float angle, const glm::vec3 &origin, const glm::vec3 &direction) :
  fov_x_{angle},
  origin_{origin},
  direction_{direction} {}

Camera::~Camera() {}

Ray Camera::compute_eye_ray(Pixel const& p) const {
  glm::vec3 pixel_3DPoint{p.x,p.y,5};
  glm::vec3 eye_ray_dir = pixel_3DPoint - origin_;
  glm::vec3 norm_eye_ray_dir = glm::normalize(eye_ray_dir);
  return Ray{origin_,norm_eye_ray_dir};
}

