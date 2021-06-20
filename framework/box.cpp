#include "box.hpp"

Box::Box(glm::vec3 const& min, glm::vec3 const& max) :
        Shape("Box",Color{0.2f,0.2f,0.2f}),
        min_{min},
        max_{max} {}

Box::Box(std::string const& str, Color const& clr, glm::vec3 const& min, glm::vec3 const& max) :
        Shape(str,clr),
        min_{min},
        max_{max} {}

float Box::area() const {
  float length = max_.x - min_.x;
  float width = max_.y - min_.y;
  float height = max_.z - min_.z;
  float area = 2 * ( (length * width) + (length * height) + (width * height) );
  return area;
}

float Box::volume() const {
  float length = max_.x - min_.x;
  float width = max_.y - min_.y;
  float height = max_.z - min_.z;
  float volume = length * width * height;
  return volume;
}