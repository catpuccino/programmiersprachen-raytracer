#ifndef SPHERE_HPP
#define SPEHRE_HPP

#include <glm/vec3.hpp>

#include "Shape.hpp"
#include "color.hpp"
#include "Ray.hpp"	//5.6
#include "HitPoint.hpp"

class Sphere : public Shape				//5.2
{
public:									//5.3
	Sphere();
	Sphere(glm::vec3 const& newcenter_, float const& newradius_);
	Sphere(glm::vec3 const& newcenter_, float const& newradius_, std::string const& newname_, Color const& newcolor_);

	~Sphere() override;							//5.8 (virtual)

	float area() const override;			
	float volume() const override;

	std::ostream& print(std::ostream& os) const override; //5.4

	HitPoint intersect(Ray const& ray) const;


private:
	glm::vec3 center_;
	float radius_;
};

#endif