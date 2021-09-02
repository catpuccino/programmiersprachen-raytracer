#ifndef PARSER_HPP
#define PARSER_HPP

#include "scene.hpp"
#include <glm/gtx/transform.hpp>
#include <string>

class SDFToolbox {
  public:
    static void parse_scene(std::string const& file_path, Scene& scene);
    static void write_rot_animation(std::string const& filename, unsigned num_frames,
        float max_degree, std::string const& obj, glm::vec3 const& axes);
};

#endif // PARSER_HPP