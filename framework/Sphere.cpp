#define _USE_MATH_DEFINES

#include "Sphere.hpp"
#include <cmath>

//5.3
Sphere::Sphere() :
	Shape::Shape("Sphere", { 1.0f,1.0f,0.0f }),
	center_{ 0.0f,0.0f,0.0f },
	radius_{ 1.0f }

{}

Sphere::Sphere(glm::vec3 const& newcenter_, float const& newradius_) :
	center_(newcenter_),
	radius_(newradius_)
{}

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


std::ostream& Sphere::print(std::ostream& os) const { //5.4
	std::ostream& osShape = Shape::print(os);
	os << "center x: " << center_.x
		<< "\t center y: " << center_.y
		<< "\t center z: " << center_.z
		<< "\n"
		<< "radius: " << radius_
		<< "\n";
	return osShape, os;
}
