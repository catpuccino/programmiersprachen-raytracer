#ifndef CAMERA_HPP
#define CAMERA_HPP

#define _USE_MATH_DEFINES
#include "ray.hpp"
#include "pixel.hpp"
#include <glm/vec3.hpp>
#include <math.h>
#include <cmath>

class Camera {
  public:
    Camera(float angle, glm::vec3 const& origin = {0.0f,0.0f,0.0f},
           glm::vec3 const& direction = {0.0f,0.0f,-1.0f});
    ~Camera();

    Ray compute_eye_ray(float x, float y, unsigned width) const;

  private:
    float fov_x_;
    glm::vec3 origin_;
    glm::vec3 direction_;
};

#endif // CAMERA_HPP
