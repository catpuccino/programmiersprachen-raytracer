#ifndef CAMERA_HPP
#define CAMERA_HPP

#define _USE_MATH_DEFINES
#include "ray.hpp"
#include "pixel.hpp"
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
#include <math.h>
#include <cmath>

class Camera {
  public:
    Camera(float angle, glm::vec3 const& position = {0.0f,0.0f,0.0f},
        glm::vec3 const& direction = { 0.0f,0.0f,-1.0f },
        glm::vec3 const& up = {0.0f, 1.0f, 0.0f});
    ~Camera();

    glm::mat4 compute_camera_transform_matrix() const;

    Ray compute_eye_ray(float pix_x, float pix_y, float distance, glm::mat4 const& camera_transform_mat) const;

    float compute_screen_distance(unsigned width) const;

    void add_to_world_transformation(glm::mat4 const& mat);

  private:
    float fov_x_;
    glm::vec3 position_;
    glm::vec3 direction_;
    glm::vec3 up_;
    glm::mat4 add_camera_transformation_; // additional camera transformation
};

#endif // CAMERA_HPP
