#ifndef BOX_HPP
#define BOX_HPP

#include "shape.hpp"
#include "ray.hpp"
#include <glm/gtx/intersect.hpp>

class Box : public Shape {
public:
    Box(glm::vec3 const& min, glm::vec3 const& max);
    Box(std::string const& str, std::shared_ptr<Material> material, glm::vec3 const& min, glm::vec3 const& max);

    glm::vec3 create_normal(HitPoint const& hp) const override;

    HitPoint intersect(Ray const& ray) const override;


private:
    glm::vec3 min_;
    glm::vec3 max_;
};

#endif // #ifndef BOX_HPP