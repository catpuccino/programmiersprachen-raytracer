#ifndef HITPOINT_HPP
#define HITPOINT_HPP

#include<glm/vec3.hpp>
#include "color.hpp"

struct HitPoint
{
	bool hit_;
	float t_;		//t = Distanz
	std::string name_;
	Color color_;
	glm::vec3 schnittpunkt_;
	glm::vec3 direction_;
};


#endif