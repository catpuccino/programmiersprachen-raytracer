#include "camera.hpp"
#include <glm/gtx/intersect.hpp>


Camera::Camera(float angle, const glm::vec3 &position, const glm::vec3 &direction, glm::vec3 const& up) :
  fov_x_{angle},
  position_{position},
  direction_{direction},
  up_{up} {}

Camera::~Camera() {}

glm::mat3x4 Camera::compute_camera_transform_matrix() const {

	// normalize vectors
	auto direction = glm::normalize(direction_);
	auto up = glm::normalize(up_);

	// vector u is orthogonal to direction & up a.k.a represents sideway direction
	glm::vec3 u = glm::normalize(glm::cross(direction, up));

	// vector v is orthogonal to u and direction, a.k.a should ideally be equal to up
	glm::vec3 v = glm::normalize(glm::cross(u, direction));

	// return transform matrix
	glm::mat3x4 transform_matrix{
		u.x, v.x, -direction.x, position_.x,
		u.y, v.y, -direction.y, position_.y,
		u.z, v.z, -direction.z, position_.z,
	};

	return transform_matrix;
}


Ray Camera::compute_eye_ray(float pix_x, float pix_y, float distance, glm::mat3x4 const& transform_mat) const {
  
  // instantiate pixel and camera position as vec4 to enable matrix multiplication 
  glm::vec4 pixel_3DPoint_vec4{pix_x, pix_y,-1* distance, 1.0f};
  glm::vec4 camera_position_vec4{ position_.x, position_.y, position_.z, 1.0f };

  // multiply points with transformation matrix
  auto pix_transformed = pixel_3DPoint_vec4 * transform_mat;
  auto pos_transformed = camera_position_vec4 * transform_mat;
  
  // change points in vec3
  glm::vec3 pixel_position{ pix_transformed.x, pix_transformed.y, pix_transformed.z };
  glm::vec3 camera_position{ pos_transformed.x, pos_transformed.y, pos_transformed.z };

  // calculate ray direction & return ray
  glm::vec3 eye_ray_dir = glm::normalize(pixel_position - camera_position);
  return Ray{ camera_position, eye_ray_dir };
}


float Camera::compute_screen_distance(unsigned width) const {
  return ((float)width / 2) / float(tan((fov_x_ / 2) * M_PI / 180));
}
