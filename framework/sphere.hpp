#ifndef SPHERE_HPP
#define SPHERE_HPP

#include "shape.hpp"

class Sphere : public Shape {
public:
    Sphere(glm::vec3 const& ctr, float r = 1.0f);
    Sphere(std::string const& str, Color const& clr, glm::vec3 const& ctr, float r = 1.0f);

    float area() const override;
    float volume() const override;
private:
    glm::vec3 centre_;
    float radius_;
};

#endif // #ifndef SPHERE_HPP