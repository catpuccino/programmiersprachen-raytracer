#ifndef PARSER_HPP
#define PARSER_HPP

#include "scene.hpp"
#include <glm/gtx/transform.hpp>
#include <string>

class SDFToolbox {
  public:
    static void parse_scene(std::string const& file_path, Scene& scene);
    static void write_rot_animation(std::string const& filename, unsigned num_frames,
        std::string const& obj, float max_degree, glm::vec3 const& axes);
    static void write_trans_animation(std::string const& filename, unsigned num_frames,
        std::string const& obj, glm::vec3 const& translate);
};

#endif // PARSER_HPP