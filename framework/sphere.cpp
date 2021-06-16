#include "sphere.hpp"

#include <cmath>

const double pi = acos(-1);

Sphere::Sphere(const glm::vec3 &ctr, float r) :
        centre_{ctr},
        radius_{r} {}

float Sphere::area() const { return 4 * float(pi) * powf(radius_,2); }

float Sphere::volume() const { return 4/3.0f * float(pi) * powf(radius_,3); }