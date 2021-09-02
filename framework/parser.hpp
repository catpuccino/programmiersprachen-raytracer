#ifndef PARSER_HPP
#define PARSER_HPP

#include "scene.hpp"
#include <glm/gtx/transform.hpp>
#include <string>

class SDFToolbox {
  public:
    static void parse_scene(std::string const& file_path, Scene& scene);
    static void write_animation(std::string const& filename, std::string const& obj, float rotation_degree, glm::vec3 const& axes);
};

#endif // PARSER_HPP