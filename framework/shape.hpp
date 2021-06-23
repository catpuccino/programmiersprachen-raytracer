#ifndef SHAPE_HPP
#define SHAPE_HPP

#include "color.hpp"
#include <glm/vec3.hpp>
#include <string>
#include <iostream>

class Shape {
  public:
    Shape(std::string const& str, Color const& clr);

    virtual float area() const = 0;
    virtual float volume() const = 0;

    virtual std::ostream& print(std::ostream& os) const;

  protected:
    std::string name_;
    Color color_;
};

std::ostream& operator<<(std::ostream& os, Shape const& s);


#endif // #ifndef SHAPE_HPP