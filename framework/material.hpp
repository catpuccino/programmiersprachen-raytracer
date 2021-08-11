#ifndef MATERIAL_HPP
#define MATERIAL_HPP

#include "color.hpp"
#include <string>

struct Material {
    std::string name;
    Color ka;
    Color kd;
    Color ks;
    float m;
    float reflection = 0.0f;
    float opacity = 1.0f;
};

std::ostream& operator<<(std::ostream& os, Material const& material);

#endif // #ifndef MATERIAL_HPP