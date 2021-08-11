#ifndef SHAPE_HPP
#define SHAPE_HPP

#include "material.hpp"
#include "color.hpp"
#include "hitpoint.hpp"
#include "ray.hpp"
#include <glm/vec3.hpp>
#include <string>
#include <iostream>

class Shape {
  public:
    Shape(std::string const& str, std::shared_ptr<Material> material);
    ~Shape();

    virtual float area() const = 0;
    virtual float volume() const = 0;
    virtual glm::vec3 normal(HitPoint const& hp) const = 0;

    virtual std::ostream& print(std::ostream& os) const;

    virtual HitPoint intersect(Ray const& ray) const = 0;

  protected:
    std::string name_;
    std::shared_ptr<Material> material_;
};

std::ostream& operator<<(std::ostream& os, Shape const& s);


#endif // #ifndef SHAPE_HPP