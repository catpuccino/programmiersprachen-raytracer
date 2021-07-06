#ifndef MATERIAL_HPP
#define MATERIAL_HPP

#include "color.hpp"
#include <string>

struct Material {
    std::string name_;
    Color ka;
    Color kd;
    Color ks;
    float m;
};

std::ostream& operator<<(std::ostream& os, Material const& material);

#endif // #ifndef MATERIAL_HPP