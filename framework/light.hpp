#ifndef LIGHT_HPP
#define LIGHT_HPP

#include "color.hpp"
#include <glm/vec3.hpp>

struct Light {
    glm::vec3 position = {0.0f,0.0f,0.0f};
    Color color = {0.5f,0.5f,0.5f};
    int brightness = 50;
};


#endif // LIGHT_HPP