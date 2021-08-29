#ifndef SPHERE_HPP
#define SPHERE_HPP

#include "shape.hpp"
#include "ray.hpp"
#include "hitpoint.hpp"
#include <glm/gtx/intersect.hpp>

class Sphere : public Shape {
public:
    Sphere(glm::vec3 const& ctr, float r = 1.0f);
    Sphere(std::string const& str, std::shared_ptr<Material> material, glm::vec3 const& ctr, float r = 1.0f);
    virtual ~Sphere();

    glm::vec3 create_normal(HitPoint const& hp) const override;

    HitPoint intersect(Ray const& ray) const override;


private:
    glm::vec3 centre_;
    float radius_;
};

#endif // #ifndef SPHERE_HPP