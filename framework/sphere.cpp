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

float Sphere::area() const { return 4 * float(pi) * powf(radius_,2); }

float Sphere::volume() const { return 4/3.0f * float(pi) * powf(radius_,3); }