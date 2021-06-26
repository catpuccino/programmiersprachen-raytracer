#ifndef SPHERE_HPP
#define SPEHRE_HPP

#include <glm/vec3.hpp>

#include "Shape.hpp"
#include "color.hpp"

class Sphere : public Shape				//5.2
{
public:									//5.3
	Sphere();
	Sphere(glm::vec3 const& newcenter_, float const& newradius_);
	Sphere(glm::vec3 const& newcenter_, float const& newradius_, std::string const& newname_, Color const& newcolor_);

	float area() const override;			
	float volume() const override;

private:
	glm::vec3 center_;
	float radius_;
};

#endif