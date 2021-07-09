#ifndef SCENE_HPP
#define SCENE_HPP

#include "material.hpp"
#include <vector>
#include <sstream>


struct Scene {
    std::vector<std::shared_ptr<Material>> material_cont;
};

void parse_materials(std::string const& file_path, Scene& scene);

#endif // #ifndef SCENE_HPP