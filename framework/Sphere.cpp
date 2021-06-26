#define _USE_MATH_DEFINES

#include "Sphere.hpp"
#include <cmath>

//5.3
Sphere::Sphere(glm::vec3 const& newcenter_, float const& newradius_, std::string const& newname_, Color const& newcolor_) :
	Shape(newname_, newcolor_),
	center_(newcenter_),
	radius_(newradius_)
{}

//5.2
float Sphere::area() const // A = 4*pi*r^2
{
	float square = radius_ * radius_;
	return abs(4 * M_PI * square);
}

float Sphere::volume() const // V = (4/3)*pi*r^3
{
	float pwrofthree = radius_ * radius_ * radius_;
	return abs((4/3) * M_PI * pwrofthree);
}
