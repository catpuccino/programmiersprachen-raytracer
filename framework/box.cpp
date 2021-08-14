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

float Box::area() const {
  float length = max_.x - min_.x;
  float width = max_.y - min_.y;
  float height = max_.z - min_.z;
  float area = 2 * ( (length * width) + (length * height) + (width * height) );
  return area;
}

float Box::volume() const {
  float length = max_.x - min_.x;
  float width = max_.y - min_.y;
  float height = max_.z - min_.z;
  float volume = length * width * height;
  return volume;
}

glm::vec3 Box::create_normal(HitPoint const& hp) const {
    auto normal = glm::cross(hp.u,hp.v);
    normal.x = fabsf(normal.x);
    normal.y = fabsf(normal.y);
    normal.z = fabsf(normal.z);
    return normal;
}

std::ostream& Box::print(std::ostream& os) const {
  Shape::print(os);
  os << "min: {" << min_.x << ", " << min_.y << ", " << min_.z << "}" << std::endl;
  os << "max: {" << max_.x << ", " << max_.y << ", " << max_.z << "}" << std::endl;
  return os;
}

HitPoint Box::intersect(Ray const& ray) const {
  bool result = false;
  float distance = 0.0f;
  float smallest_dist = std::numeric_limits<float>::max(); /* smallest distance between intersection
                                                              and ray origin */
  // directional vectors for normal
  glm::vec3 u = { 0.0f, 0.0f, 0.0f };
  glm::vec3 v = { 0.0f, 0.0f, 0.0f };

  // left side of AABB
  float p_x = min_.x;
  float t = (p_x - ray.origin.x) / ray.direction.x;
  float p_y = ray.origin.y + t * ray.direction.y;
  float p_z = ray.origin.z + t * ray.direction.z;
  distance = glm::distance(glm::vec3{p_x,p_y,p_z},ray.origin);
  if (min_.y <= p_y && p_y <= max_.y && min_.z <= p_z && p_z <= max_.z && t >= 0) {
    smallest_dist = distance;
    result = true;
    // sets dir-vectors along bottom-back & left-back edges
    u = { 0.0f, 1.0f, 0.0f };
    v = { 0.0f, 0.0f, 1.0f };
  }

  // right side of AABB
  p_x = max_.x;
  t = (p_x - ray.origin.x) / ray.direction.x;
  p_y = ray.origin.y + t * ray.direction.y;
  p_z = ray.origin.z + t * ray.direction.z;
  distance = glm::distance(glm::vec3{p_x,p_y,p_z},ray.origin);
  if (min_.y <= p_y && p_y <= max_.y && min_.z <= p_z && p_z <= max_.z && distance < smallest_dist && t >= 0) {
    smallest_dist = distance;
    result = true;
    // sets dir-vectors along bottom-back & right-back edges
    u = { 0.0f, 1.0f, 0.0f };
    v = { 0.0f, 0.0f, 1.0f };
  }

  // front side of AABB
  p_y = min_.y;
  t = (p_y - ray.origin.y) / ray.direction.y;
  p_x = ray.origin.x + t * ray.direction.x;
  p_z = ray.origin.z + t * ray.direction.z;
  distance = glm::distance(glm::vec3{p_x,p_y,p_z},ray.origin);
  if (min_.x <= p_x && p_x <= max_.x && min_.z <= p_z && p_z <= max_.z && distance < smallest_dist && t >= 0) {
    smallest_dist = distance;
    result = true;
    // sets dir-vectors along bottom-left & back-left edges
    u = { 1.0f, 0.0f, 0.0f };
    v = { 0.0f, 0.0f, 1.0f };
  }

  // back side of AABB
  p_y = max_.y;
  t = (p_y - ray.origin.y) / ray.direction.y;
  p_x = ray.origin.x + t * ray.direction.x;
  p_z = ray.origin.z + t * ray.direction.z;
  distance = glm::distance(glm::vec3{p_x,p_y,p_z},ray.origin);
  if (min_.x <= p_x && p_x <= max_.x && min_.z <= p_z && p_z <= max_.z && distance < smallest_dist && t >= 0) {
    smallest_dist = distance;
    result = true;
    // sets dir-vectors along bottom-right & back-right edges
    u = { 1.0f, 0.0f, 0.0f };
    v = { 0.0f, 0.0f, 1.0f };
  }

  // bottom side of AABB
  p_z = min_.z;
  t = (p_z - ray.origin.z) / ray.direction.z;
  p_x = ray.origin.x + t * ray.direction.x;
  p_y = ray.origin.y + t * ray.direction.y;
  distance = glm::distance(glm::vec3{p_x,p_y,p_z},ray.origin);
  if (min_.x <= p_x && p_x <= max_.x && min_.y <= p_y && p_y <= max_.y && distance < smallest_dist && t >= 0) {
    smallest_dist = distance;
    result = true;
    // sets dir-vectors along bottom-left & bottom-back edges
    u = { 1.0f, 0.0f, 0.0f };
    v = { 0.0f, 1.0f, 0.0f };
  }

  // top side of AABB
  p_z = max_.z;
  t = (p_z - ray.origin.z) / ray.direction.z;
  p_x = ray.origin.x + t * ray.direction.x;
  p_y = ray.origin.y + t * ray.direction.y;
  distance = glm::distance(glm::vec3{p_x,p_y,p_z},ray.origin);
  if (min_.x <= p_x && p_x <= max_.x && min_.y <= p_y && p_y <= max_.y && distance < smallest_dist && t >= 0) {
    smallest_dist = distance;
    result = true;
    // sets dir-vectors along top-left & top-back edges
    u = { 1.0f, 0.0f, 0.0f };
    v = { 0.0f, 1.0f, 0.0f };
  }

  glm::vec3 normalized_ray_direction = glm::normalize(ray.direction);
  glm::vec3 hitpoint = ray.origin + smallest_dist * normalized_ray_direction; //

  return HitPoint{result,smallest_dist,name_,material_,hitpoint,normalized_ray_direction, u, v};
}

