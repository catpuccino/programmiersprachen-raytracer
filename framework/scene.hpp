#ifndef SCENE_HPP
#define SCENE_HPP

#include "material.hpp"
#include <vector>

struct Scene {
    std::vector<std::shared_ptr<Material>> material_cont;
};

#endif // #ifndef SCENE_HPP