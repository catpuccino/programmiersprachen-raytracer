#ifndef SHAPE_HPP
#define SHAPE_HPP

#include "material.hpp"
#include "color.hpp"
#include "hitpoint.hpp"
#include "ray.hpp"
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtx/intersect.hpp>
#include <string>
#include <iostream>

class Shape {
  public:
    Shape(std::string const& str, std::shared_ptr<Material> material);
    ~Shape();

    virtual glm::vec3 create_normal(HitPoint const& hp) const = 0;

    virtual HitPoint intersect(Ray const& ray) const = 0;

    void add_to_world_transformation(glm::mat4 const& frac_transform_mat, glm::mat4 const& frac_transform_mat_inv);

    Ray transformRay(Ray const& ray) const;

    HitPoint transform_objSpace_hp_to_wrldSpace(HitPoint const& hp) const;

  protected:
    std::string name_;
    std::shared_ptr<Material> material_;
    glm::mat4 world_transformation_;
    glm::mat4 world_transformation_inv_;
};

#endif // #ifndef SHAPE_HPP