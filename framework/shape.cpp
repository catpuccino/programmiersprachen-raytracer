#include "shape.hpp"

Shape::Shape(std::string const& str, std::shared_ptr<Material> material) :
        name_{str},
        material_{material} {}

Shape::~Shape() {}

std::ostream& Shape::print(std::ostream& os) const {
  os << "Name: " << name_ << std::endl;
  os << "Material: " << material_ << std::endl;
  return os;
}

std::ostream& operator<<(std::ostream& os, Shape const& s) {
  return s.print(os);
}