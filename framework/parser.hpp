#ifndef PARSER_HPP
#define PARSER_HPP

#include "scene.hpp"
#include <glm/gtx/transform.hpp>
#include <string>

class SDFParser {
  public:
    static void parse_scene(std::string const& file_path, Scene& scene);
    static glm::mat4 make_translate(float t_x, float t_y, float t_z);
    static glm::mat4 make_rotate(float degree, glm::vec3 const& r_axis);
    static glm::mat4 make_scale(float s_x, float s_y, float s_z);
};

#endif // PARSER_HPP