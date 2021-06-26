#include "Box.hpp"

//5.3
Box::Box() :
	Shape::Shape("Sphere", { 0.0f,1.0f,1.0f }),
	min_({ 0.0f,0.0f,0.0f }),
	max_({ 1.0f, 1.0f, 1.0f })
{}

Box::Box(glm::vec3 const& newmin_, glm::vec3 const& newmax_) :
	min_(newmin_),
	max_(newmax_)
{}

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


std::ostream& Box::print(std::ostream& os) const //5.4
{
	std::ostream& osShape = Shape::print(os);
	os << "min x: " << min_.x
		<< "\t min y: " << min_.y
		<< "\t min z: " << min_.z
		<< "\n"
		<< "max x : " << max_.x
		<< "\t max y: " << max_.y
		<< "\t max z: " << max_.z
		<< "\n";
	return osShape,os;
}
