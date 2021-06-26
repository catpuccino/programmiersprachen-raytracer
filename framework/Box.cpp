#include "Box.hpp"

//5.3
Box::Box(glm::vec3 const& newmin_, glm::vec3 const& newmax_, std::string const& newname_, Color const& newcolor_) :
	Shape(newname_, newcolor_),
	min_(newmin_),
	max_(newmax_)
{}

//5.2
float Box::area() const  // A = 2*l*w + 2*l*h + 2*w*h
{
	float length = max_.x - min_.x;
	float height = max_.y - min_.y;
	float width = max_.z - min_.z;
	return abs(2 * length * width + 2 * length * height + 2 * width * height);


}

float Box::volume() const	// V = l*h*w
{
	float length = max_.x - min_.x;
	float height = max_.y - min_.y;
	float width = max_.z - min_.z;
	return abs(length * height * width);
}
