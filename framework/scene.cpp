#include "scene.hpp"

#include <fstream>

void parse_materials(std::string const& file_path, Scene& scene) {

  std::ifstream in_sdf_file(file_path);

  std::string line_buffer = "";
  // loop over file and read it line by line
  while (std::getline(in_sdf_file, line_buffer)) {

    std::istringstream line_as_string_stream(line_buffer);
    std::string token_string = "";

    line_as_string_stream >> token_string;
    // jz was mit token_string machen
    if (!("define" == token_string)) {
      return;
    }

    std::string object_string = "";
    line_as_string_stream >> object_string;

    if ("material" == object_string) {
      // read all attributes for material, than create it
      std::string material_name = "";
      line_as_string_stream >> material_name;

      Color k_a = {0.0f, 0.0f, 0.0f};
      line_as_string_stream >> k_a.r;
      line_as_string_stream >> k_a.g;
      line_as_string_stream >> k_a.b;

      Color k_d = {0.0f, 0.0f, 0.0f};
      line_as_string_stream >> k_d.r;
      line_as_string_stream >> k_d.g;
      line_as_string_stream >> k_d.b;

      Color k_s = {0.0f, 0.0f, 0.0f};
      line_as_string_stream >> k_s.r;
      line_as_string_stream >> k_s.g;
      line_as_string_stream >> k_s.b;

      float m = 0.0f;
      line_as_string_stream >> m;

      std::shared_ptr<Material> material = std::make_shared<Material>(Material{material_name,
                                                                               k_a, k_d, k_s, m});
      scene.material_cont.push_back(material);
    }
  }

  in_sdf_file.close();
}