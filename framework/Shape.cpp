#include "Shape.hpp"
#include "color.hpp"


Shape::Shape():
	name_("Arthur Dent - my default shape"),
	color_({ 1.0f,1.0f,1.0f })
{}

Shape::Shape(std::string const& newname_, Color const& newcolor_):		//5.3
	name_(newname_),
	color_(newcolor_)
{}