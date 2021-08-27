#include "shape.hpp"

Shape::Shape(std::string const& str, std::shared_ptr<Material> material) :
        name_{str},
        material_{material} {}

Shape::~Shape() {}

std::ostream& Shape::print(std::ostream& os) const {
  os << "Name: " << name_ << std::endl;
  os << "Material: " << material_ << std::endl;
  return os;
}

std::ostream& operator<<(std::ostream& os, Shape const& s) {
  return s.print(os);
}

void Shape::set_transform_matrix(glm::mat4 const& transform_matrix, glm::mat4 const& transform_matrix_inv) {
  world_transformation_ = transform_matrix;
  world_transformation_inv_ = transform_matrix_inv;
}

Ray Shape::transformRay(Ray const& ray) const {
  // express ray origin and direction as homogenous coordinates (vec4)
  glm::vec4 ray_origin_vec4 = {ray.origin.x,ray.origin.y,ray.origin.z, 1.0f};
  glm::vec4 ray_dir_vec4 = {ray.direction.x,ray.direction.y,ray.direction.z, 0.0f};

  // apply transformation to ray origin & direction
  glm::vec4 ray_origin_transformed = ray_origin_vec4 * world_transformation_inv_;
  glm::vec4 ray_dir_transformed = ray_dir_vec4 * world_transformation_inv_;

  // cast origin & direction vectors back to 3D
  glm::vec3 new_ray_origin = {ray_origin_transformed.x,ray_origin_transformed.y,ray_origin_transformed.z};
  glm::vec3 new_ray_dir = glm::normalize(glm::vec3({ray_dir_transformed.x,ray_dir_transformed.y,ray_dir_transformed.z}));

  return Ray{new_ray_origin,new_ray_dir};
}

HitPoint Shape::transform_objSpace_hp_to_wrldSpace(HitPoint const& hp) const {
  /* now transform object-space hitpoint and normal to world-space
     by using world_transformation_ matrix */

  // express hitpoint and normal as homogenous coordinates (vec4)
  glm::vec4 os_hitpoint_vec4 = {hp.hitpoint.x, hp.hitpoint.y, hp.hitpoint.z, 1.0f};
  glm::vec4 os_hit_dir_vec4 = { hp.hit_direction.x, hp.hit_direction.y, hp.hit_direction.z, 0.0f };
  glm::vec4 os_normal_vec4 = {hp.normal.x, hp.normal.y, hp.normal.z, 0.0f};

  // apply transformation to object-space hitpoint & normal
  glm::vec4 ws_hitpoint_vec4 = os_hitpoint_vec4 * world_transformation_;
  glm::vec4 ws_hit_dir_vec4 = os_hit_dir_vec4 * world_transformation_;
  glm::vec4 ws_normal_vec4 = os_normal_vec4 * glm::transpose(world_transformation_inv_);

  // cast origin & direction vectors back to 3D (ws = world-space)
  glm::vec3 ws_hitpoint = { ws_hitpoint_vec4.x, ws_hitpoint_vec4.y, ws_hitpoint_vec4.z };
  glm::vec3 ws_hit_dir = glm::normalize(glm::vec3{ ws_hit_dir_vec4.x, ws_hit_dir_vec4.y, ws_hit_dir_vec4.z});
  glm::vec3 ws_normal = glm::normalize(glm::vec3{ws_normal_vec4.x, ws_normal_vec4.y, ws_normal_vec4.z});

  // instantiate world-space hitpoint
  HitPoint world_hp{hp};
  world_hp.hitpoint = ws_hitpoint;
  world_hp.normal = ws_normal;
  world_hp.hit_direction = ws_hit_dir;

  return world_hp;
}