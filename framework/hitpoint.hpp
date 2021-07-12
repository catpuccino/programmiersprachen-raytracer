#ifndef HITPOINT_HPP
#define HITPOINT_HPP

#include "color.hpp"
#include <glm/vec3.hpp>
#include <string>

struct HitPoint
{
    bool did_intersect;
    float distance;
    std::string name;
    std::shared_ptr<Material> material;
    glm::vec3 hitpoint;
    glm::vec3 hit_direction;
};

#endif // #ifndef HITPOINT_HPP