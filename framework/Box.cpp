#include "Box.hpp"

Box::Box(glm::vec3 const& newmin_, glm::vec3 const& newmax_, Color const& newcolor_) 
{
	min_ = newmin_;
	max_ = newmax_;
	color_ = newcolor_;
}