#include "Sphere.hpp"

Sphere::Sphere(glm::vec3 const& newcenter_, float const& newradius_, Color const& newcolor_)
{
	center_ = newcenter_;
	radius_ = newradius_;
	color_ = newcolor_;
}