#include "camera.hpp"

Camera::Camera(float angle, const glm::vec3 &origin, const glm::vec3 &direction) :
  fov_x_{angle},
  origin_{origin},
  direction_{direction} {}

Camera::~Camera() {}

