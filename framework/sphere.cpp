#include "sphere.hpp"

Sphere::Sphere(glm::vec3 const& ctr, float r) :
        Shape{"Sphere", std::make_shared<Material>(Material{"Standard",
                                                            {0.5f,0.5f,0.5f},
                                                            {0.5f,0.5f,0.5f},
                                                            {0.5f,0.5f,0.5f},
                                                            2.0f})},
        centre_{ctr},
        radius_{r} {}

Sphere::Sphere(std::string const& str, std::shared_ptr<Material> material, glm::vec3 const& ctr, float r) :
        Shape(str,material),
        centre_{ctr},
        radius_{r} {}

Sphere::~Sphere() {}


glm::vec3 Sphere::create_normal(HitPoint const& hp) const {
    auto normal = hp.hitpoint - centre_;
    auto normal_normalized = glm::normalize(normal);
    return normal_normalized;
}

HitPoint Sphere::intersect(Ray const& ray) const {
  glm::vec3 obs_center = {0.0f, 0.0f, 0.0f}; // object-space center_
  float obs_radius = 1.0f; // object-space radius_

  float distance = 0.0f;
  glm::vec3 normalized_ray_direction = glm::normalize(ray.direction);
  auto result = glm::intersectRaySphere(
          ray.origin,
          normalized_ray_direction,
          obs_center,
          obs_radius * obs_radius,
          distance);
  glm::vec3 hitpoint = ray.origin + distance * normalized_ray_direction;

  // create normal
  auto normal = hitpoint - obs_center;
  auto normal_normalized = glm::normalize(normal);

  return HitPoint{result,distance,name_,material_,hitpoint,normalized_ray_direction,normal_normalized};
}



