#ifndef HITPOINT_HPP
#define HITPOINT_HPP

#include "color.hpp"
#include <glm/vec3.hpp>
#include <string>

struct HitPoint
{
    bool did_intersect;
    float t;
    std::string name;
    Color color;
    glm::vec3 hitpoint;
    glm::vec3 hit_direction;
};

#endif // #ifndef HITPOINT_HPP