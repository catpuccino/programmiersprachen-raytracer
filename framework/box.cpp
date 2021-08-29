#include "box.hpp"


Box::Box(glm::vec3 const& min, glm::vec3 const& max) :
        Shape{"Box",std::make_shared<Material>(Material{"Standard",
                                                        {0.5f,0.5f,0.5f},
                                                        {0.5f,0.5f,0.5f},
                                                        {0.5f,0.5f,0.5f},
                                                        2.0f})},
        min_{min},
        max_{max} {}


Box::Box(std::string const& str, std::shared_ptr<Material> material, glm::vec3 const& min, glm::vec3 const& max) :
        Shape(str,material),
        min_{min},
        max_{max} {}


glm::vec3 Box::create_normal(HitPoint const& hp) const {
    return hp.normal;
}


HitPoint Box::intersect(Ray const& ray) const {
  glm::vec3 obs_min = { -0.5f, -0.5f, -0.5f }; // object-space min_
  glm::vec3 obs_max = { 0.5f, 0.5f, 0.5f }; // object-space max_

  bool result = false;
  float distance = 0.0f;
  float smallest_dist = std::numeric_limits<float>::max(); /* smallest distance between intersection
                                                              and ray origin */
  // normal vector for intersection point
  glm::vec3 n = { 0.0f, 0.0f, 0.0f };

  // left side of AABB
  float p_x = obs_min.x;
  float t = (p_x - ray.origin.x) / ray.direction.x;
  float p_y = ray.origin.y + t * ray.direction.y;
  float p_z = ray.origin.z + t * ray.direction.z;
  distance = glm::distance(glm::vec3{p_x,p_y,p_z},ray.origin);
  if (obs_min.y <= p_y && p_y <= obs_max.y && obs_min.z <= p_z && p_z <= obs_max.z && t >= 0) {
    smallest_dist = distance;
    result = true;
    // sets dir-vectors along bottom-back & left-back edges
    n = { -1.0f, 0.0f, 0.0f };
  }

  // right side of AABB
  p_x = obs_max.x;
  t = (p_x - ray.origin.x) / ray.direction.x;
  p_y = ray.origin.y + t * ray.direction.y;
  p_z = ray.origin.z + t * ray.direction.z;
  distance = glm::distance(glm::vec3{p_x,p_y,p_z},ray.origin);
  if (obs_min.y <= p_y && p_y <= obs_max.y && obs_min.z <= p_z && p_z <= obs_max.z && distance < smallest_dist && t >= 0) {
    smallest_dist = distance;
    result = true;
    // sets dir-vectors along bottom-back & right-back edges
    n = { 1.0f, 0.0f, 0.0f };
  }

  // front side of AABB
  p_y = obs_min.y;
  t = (p_y - ray.origin.y) / ray.direction.y;
  p_x = ray.origin.x + t * ray.direction.x;
  p_z = ray.origin.z + t * ray.direction.z;
  distance = glm::distance(glm::vec3{p_x,p_y,p_z},ray.origin);
  if (obs_min.x <= p_x && p_x <= obs_max.x && obs_min.z <= p_z && p_z <= obs_max.z && distance < smallest_dist && t >= 0) {
    smallest_dist = distance;
    result = true;
    // sets dir-vectors along bottom-left & back-left edges
    n = { 0.0f, -1.0f, 0.0f };
  }

  // back side of AABB
  p_y = obs_max.y;
  t = (p_y - ray.origin.y) / ray.direction.y;
  p_x = ray.origin.x + t * ray.direction.x;
  p_z = ray.origin.z + t * ray.direction.z;
  distance = glm::distance(glm::vec3{p_x,p_y,p_z},ray.origin);
  if (obs_min.x <= p_x && p_x <= obs_max.x && obs_min.z <= p_z && p_z <= obs_max.z && distance < smallest_dist && t >= 0) {
    smallest_dist = distance;
    result = true;
    // sets dir-vectors along bottom-right & back-right edges
    n = { 0.0f, 1.0f, 0.0f };
  }

  // bottom side of AABB
  p_z = obs_min.z;
  t = (p_z - ray.origin.z) / ray.direction.z;
  p_x = ray.origin.x + t * ray.direction.x;
  p_y = ray.origin.y + t * ray.direction.y;
  distance = glm::distance(glm::vec3{p_x,p_y,p_z},ray.origin);
  if (obs_min.x <= p_x && p_x <= obs_max.x && obs_min.y <= p_y && p_y <= obs_max.y && distance < smallest_dist && t >= 0) {
    smallest_dist = distance;
    result = true;
    // sets dir-vectors along bottom-left & bottom-back edges
    n = { 0.0f, 0.0f, -1.0f };
  }

  // top side of AABB
  p_z = obs_max.z;
  t = (p_z - ray.origin.z) / ray.direction.z;
  p_x = ray.origin.x + t * ray.direction.x;
  p_y = ray.origin.y + t * ray.direction.y;
  distance = glm::distance(glm::vec3{p_x,p_y,p_z},ray.origin);
  if (obs_min.x <= p_x && p_x <= obs_max.x && obs_min.y <= p_y && p_y <= obs_max.y && distance < smallest_dist && t >= 0) {
    smallest_dist = distance;
    result = true;
    // sets dir-vectors along top-left & top-back edges
    n = { 0.0f, 0.0f, 1.0f };
  }

  glm::vec3 normalized_ray_direction = glm::normalize(ray.direction);
  glm::vec3 hitpoint = ray.origin + smallest_dist * normalized_ray_direction; //

  return HitPoint{result,smallest_dist,name_,material_,hitpoint,normalized_ray_direction, n};
}



