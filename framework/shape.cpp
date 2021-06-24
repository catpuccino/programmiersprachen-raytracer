#include "shape.hpp"

Shape::Shape(std::string const& str, const Color &clr) :
        name_{str},
        color_{clr} { std::cout << "Shape Constructor" << std::endl; }

Shape::~Shape() { std::cout << "Shape Destructor" << std::endl; }

std::ostream& Shape::print(std::ostream& os) const {
  os << "Name: " << name_ << std::endl;
  os << "Color: " << color_.r << ", " << color_.g << ", " << color_.b << std::endl;
  return os;
}

std::ostream& operator<<(std::ostream& os, Shape const& s) {
  return s.print(os);
}