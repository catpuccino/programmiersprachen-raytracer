#ifndef PARSER_HPP
#define PARSER_HPP

#include "scene.hpp"
#include <string>

class SDFParser {
  public:
    static void parse_objects(std::string const& file_path, Scene& scene);
};

#endif // PARSER_HPP