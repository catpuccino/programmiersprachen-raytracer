#include "parser.hpp"

#include <fstream>

void SDFParser::parse_scene(std::string const& file_path, Scene& scene) {

  std::ifstream in_sdf_file(file_path);

  std::string line_buffer;
  // loop over file and read it line by line
  while (std::getline(in_sdf_file, line_buffer)) {

    std::istringstream line_as_string_stream(line_buffer);
    std::string token_string;

    line_as_string_stream >> token_string;

    if ("#" == token_string) {
      continue;
    }

    std::string object_string;
    line_as_string_stream >> object_string;

    if ("material" == object_string) {
      // read all attributes for material, then create it
      std::string material_name;
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

      float reflection = 0.0f;
      line_as_string_stream >> reflection;

      float opacity = 1.0f;
      line_as_string_stream >> opacity;

      float refraction_index = 1.0f;
      line_as_string_stream >> refraction_index;

      std::shared_ptr<Material> material = std::make_shared<Material>(Material{material_name,
                                                                               k_a, k_d, k_s, m,
                                                                               reflection, opacity,
                                                                               refraction_index});
      scene.material_cont.try_emplace(material_name,material);
    }

    if ("shape" == object_string) {
      // check shape specification
      std::string shape_object;
      line_as_string_stream >> shape_object;

      if ("box" == shape_object) {
        std::string box_name;
        line_as_string_stream >> box_name;

        glm::vec3 box_min{0.0f,0.0f,0.0f};
        line_as_string_stream >> box_min.x;
        line_as_string_stream >> box_min.y;
        line_as_string_stream >> box_min.z;

        glm::vec3 box_max{0.0f,0.0f,0.0f};
        line_as_string_stream >> box_max.x;
        line_as_string_stream >> box_max.y;
        line_as_string_stream >> box_max.z;

        std::string box_material_name;
        line_as_string_stream >> box_material_name;

        std::shared_ptr<Material> box_material;

        auto i = scene.material_cont.find(box_material_name);
        if (i != scene.material_cont.end()) {
          box_material = i->second;
        } else {
          return;
        }

        std::shared_ptr<Shape> box = std::make_shared<Box>(Box{box_name,box_material,
                                                               box_min,box_max});

        scene.shape_cont.try_emplace(box_name,box);
      }

      if ("sphere" == shape_object) {
        std::string sphere_name;
        line_as_string_stream >> sphere_name;

        glm::vec3 sphere_center{0.0f,0.0f,0.0f};
        line_as_string_stream >> sphere_center.x;
        line_as_string_stream >> sphere_center.y;
        line_as_string_stream >> sphere_center.z;

        float sphere_radius = 0.0f;
        line_as_string_stream >> sphere_radius;

        std::string sphere_material_name;
        line_as_string_stream >> sphere_material_name;

        std::shared_ptr<Material> sphere_material;

        auto i = scene.material_cont.find(sphere_material_name);
        if (i != scene.material_cont.end()) {
          sphere_material = i->second;
        } else {
          return;
        }

        std::shared_ptr<Shape> sphere = std::make_shared<Sphere>(Sphere{sphere_name,sphere_material,
                                                                        sphere_center,sphere_radius});

        scene.shape_cont.try_emplace(sphere_name,sphere);
      }
    }

    if ("light" == object_string) {
      std::string light_name;
      line_as_string_stream >> light_name;

      glm::vec3 light_position{0.0f,0.0f,0.0f};
      line_as_string_stream >> light_position.x;
      line_as_string_stream >> light_position.y;
      line_as_string_stream >> light_position.z;

      Color light_color{0.0f,0.0f,0.0f};
      line_as_string_stream >> light_color.r;
      line_as_string_stream >> light_color.g;
      line_as_string_stream >> light_color.b;

      int light_brightness = 0;
      line_as_string_stream >> light_brightness;

      std::shared_ptr<Light> light = std::make_shared<Light>(Light{light_position,light_color,
                                                                   light_brightness});
      scene.light_cont.try_emplace(light_name,light);
    }

    if ("camera" == object_string) {
      std::string camera_name;
      line_as_string_stream >> camera_name;

      float camera_angle = 0.0f;
      line_as_string_stream >> camera_angle;

      glm::vec3 position{ 0.0f,0.0f,0.0f };
      line_as_string_stream >> position.x;
      line_as_string_stream >> position.y;
      line_as_string_stream >> position.z;

      glm::vec3 direction{ 0.0f, 0.0f, -1.0f };
      line_as_string_stream >> direction.x;
      line_as_string_stream >> direction.y;
      line_as_string_stream >> direction.z;

      glm::vec3 up{ 0.0f, 1.0f, 0.0f };
      line_as_string_stream >> up.x;
      line_as_string_stream >> up.y;
      line_as_string_stream >> up.z;

      Camera camera{camera_angle, position, direction, up};

      scene.camera = camera;
    }

    if ("transform" == object_string) {
        std::string object_name;
        line_as_string_stream >> object_name;

        std::string transform_string;
        line_as_string_stream >> transform_string;

        glm::mat4 unit_matrix{
            1.0f, 0.0f, 0.0f, 0.0f,
            0.0f, 1.0f, 0.0f, 0.0f,
            0.0f, 0.0f, 1.0f, 0.0f,
            0.0f, 0.0f, 0.0f, 1.0f
        }; 

        auto translate_matrix = unit_matrix;
        auto translate_matrix_inv = unit_matrix;

        auto scale_matrix = unit_matrix;
        auto scale_matrix_inv = unit_matrix;

        auto rotation_matrix = unit_matrix;
        auto rotation_matrix_inv = unit_matrix;

        // inistantiate translate matrix
        if ("translate" == transform_string) {
            float translate_x;
            float translate_y;
            float translate_z;
            line_as_string_stream >> translate_x;
            line_as_string_stream >> translate_y;
            line_as_string_stream >> translate_z;

            translate_matrix = {
                1.0f, 0.0f, 0.0f, translate_x,
                0.0f, 1.0f, 0.0f, translate_y,
                0.0f, 0.0f, 1.0f, translate_z,
                0.0f, 0.0f, 0.0f, 1.0f
            };

            translate_matrix_inv = {
                1.0f, 0.0f, 0.0f, -translate_x,
                0.0f, 1.0f, 0.0f, -translate_y,
                0.0f, 0.0f, 1.0f, -translate_z,
                0.0f, 0.0f, 0.0f, 1.0f
            };


        }

        // calculate world transformation matrix
        glm::mat4 transform_mat = translate_matrix * scale_matrix * rotation_matrix;
        glm::mat4 tranform_mat_inv = translate_matrix_inv;
        


        // find shape to transform and set tranformation matrices
        auto transform_shape = scene.shape_cont.find(object_name);
        (*(*transform_shape).second).set_transform_matrix(transform_mat, tranform_mat_inv);
    }
  }

  in_sdf_file.close();
}