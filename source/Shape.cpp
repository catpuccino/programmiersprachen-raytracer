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

Shape::~Shape() {}														//5.8


std::ostream& operator<<(std::ostream& os, Shape const& s) {				//5.4
	return os << s;
}

std::ostream& Shape::print(std::ostream& os) const {
	os	<< "\n"
		<< "name: " << name_
		<< "\n"
		<< "color: " << color_;

	return os;
}