#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <glm/vec3.hpp>

class Camera {
  public:
    Camera(float angle, glm::vec3 const& origin = {0.0f,0.0f,0.0f},
           glm::vec3 const& direction = {0.0f,0.0f,-1.0f});
    ~Camera();

  private:
    float fov_x_;
    glm::vec3 origin_;
    glm::vec3 direction_;
};

#endif // CAMERA_HPP
