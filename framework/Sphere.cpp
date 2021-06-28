#define _USE_MATH_DEFINES

#include "Sphere.hpp"
#include <cmath>

#include <glm/glm.hpp>				//5.6
#include <glm/gtx/intersect.hpp>


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


Sphere::~Sphere() {}						//5.8 (virtual)

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

//5.6
HitPoint Sphere::intersect(Ray const& ray) const
{
	// Point p = Ray_origin + Ray_direction * time
	// time = dot(center_sphere - ray_origin, ray_direction)
	// float x? = length(center_sphere - Point p)
	// float y?...

	HitPoint hp;

	hp.name_ = name_;
	hp.color_ = color_;
	hp.direction_ = ray.direction;

	float distance = 0.0f;
	hp.hit_ = glm::intersectRaySphere(
		ray.origin, ray.direction, center_,
		radius_ * radius_, //squard radius!!
		distance);
	hp.t_ = distance;

	//still missing: vec3 schnittpunkt, pythagoras stuff? ray.origin and ray.direction and distance?
	return hp;
}
