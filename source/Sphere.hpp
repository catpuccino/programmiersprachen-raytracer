#ifndef SPHERE_HPP
#define SPEHRE_HPP

#include <glm/vec3.hpp>

#include "Shape.hpp"
#include "color.hpp"

class Sphere : public Shape				//5.2
{
public:
	Sphere(glm::vec3 const& newcenter_, float const& newradius_, Color const& newcolor_);

	float area() const override;			
	float volume() const override;

private:
	glm::vec3 center_;
	float radius_;
	Color color_;
};

#endif