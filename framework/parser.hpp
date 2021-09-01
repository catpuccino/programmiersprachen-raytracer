#ifndef PARSER_HPP
#define PARSER_HPP

#include "scene.hpp"
#include <glm/gtx/transform.hpp>
#include <string>

class SDFToolbox {
  public:
    static void parse_scene(std::string const& file_path, Scene& scene);
    static void write_scene(unsigned current_frame, std::string const& filename, float rotation_degree);
};

#endif // PARSER_HPP