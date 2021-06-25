#ifndef BOX_HPP
#define BOX_HPP

#include <glm/vec3.hpp>


#include "Shape.hpp"
#include "color.hpp"

class Box : public Shape			//5.2
{
public:
	Box(glm::vec3 const& newmin_, glm::vec3 const& newmax_, Color const& newcolor_);

	float area() const override;
	float volume() const override;

private:
	glm::vec3 min_;
	glm::vec3 max_;
	Color color_;
};

#endif