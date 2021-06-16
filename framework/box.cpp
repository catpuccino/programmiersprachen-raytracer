#include "box.hpp"

Box::Box(const glm::vec3 &min, const glm::vec3 &max) :
        min_{min},
        max_{max} {}

float Box::area() const { return 0; }

float Box::volume() const {return 0;}