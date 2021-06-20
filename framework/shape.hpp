#ifndef SHAPE_HPP
#define SHAPE_HPP

#include "color.hpp"
#include <glm/vec3.hpp>
#include <string>

class Shape {
  public:
    Shape(std::string const& str, Color const& clr);

    virtual float area() const = 0;
    virtual float volume() const = 0;
  private:
    std::string name_;
    Color color_;
};

#endif // #ifndef SHAPE_HPP