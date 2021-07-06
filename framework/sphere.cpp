#include "sphere.hpp"

#include <cmath>

const double pi = acos(-1);

Sphere::Sphere(glm::vec3 const& ctr, float r) :
        Shape("Sphere",Color{0.5f,0.5f,0.5f}),
        centre_{ctr},
        radius_{r} {}

Sphere::Sphere(std::string const& str, Color const& clr, glm::vec3 const& ctr, float r) :
        Shape(str,clr),
        centre_{ctr},
        radius_{r} {}

Sphere::~Sphere() {}

float Sphere::area() const { return 4 * float(pi) * powf(radius_,2); }

float Sphere::volume() const { return 4/3.0f * float(pi) * powf(radius_,3); }

HitPoint Sphere::intersect(Ray const& ray) const {
  float distance = 0.0f;
  glm::vec3 normalized_ray_direction = glm::normalize(ray.direction);
  auto result = glm::intersectRaySphere(
          ray.origin,
          normalized_ray_direction,
          centre_,
          radius_ * radius_,
          distance);
  glm::vec3 hitpoint = ray.origin + distance * normalized_ray_direction;

  return HitPoint{result,distance,name_,color_,hitpoint,normalized_ray_direction};
}

std::ostream& Sphere::print(std::ostream& os) const {
  Shape::print(os);
  os << "Centre: {" << centre_.x << ", " << centre_.y << ", " << centre_.z << "}" << std::endl;
  os << "Radius: " << radius_ << std::endl;
  return os;
}

