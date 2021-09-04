#include "parser.hpp"

#include <fstream>


void SDFToolbox::parse_scene(std::string const& file_path, Scene& scene) {

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

        if ("define" == token_string) {
            std::string object_string;
            line_as_string_stream >> object_string;

            if ("material" == object_string) {
                // read all attributes for material, then create it
                std::string material_name;
                line_as_string_stream >> material_name;

                Color k_a = { 0.0f, 0.0f, 0.0f };
                line_as_string_stream >> k_a.r;
                line_as_string_stream >> k_a.g;
                line_as_string_stream >> k_a.b;

                Color k_d = { 0.0f, 0.0f, 0.0f };
                line_as_string_stream >> k_d.r;
                line_as_string_stream >> k_d.g;
                line_as_string_stream >> k_d.b;

                Color k_s = { 0.0f, 0.0f, 0.0f };
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

                std::shared_ptr<Material> material = std::make_shared<Material>(Material{ material_name,
                                                                                         k_a, k_d, k_s, m,
                                                                                         reflection, opacity,
                                                                                         refraction_index });
                scene.material_cont.try_emplace(material_name, material);
            }

            if ("shape" == object_string) {
                // check shape specification
                std::string shape_object;
                line_as_string_stream >> shape_object;

                if ("box" == shape_object) {
                    std::string box_name;
                    line_as_string_stream >> box_name;

                    glm::vec3 box_min{ 0.0f,0.0f,0.0f };
                    line_as_string_stream >> box_min.x;
                    line_as_string_stream >> box_min.y;
                    line_as_string_stream >> box_min.z;

                    glm::vec3 box_max{ 0.0f,0.0f,0.0f };
                    line_as_string_stream >> box_max.x;
                    line_as_string_stream >> box_max.y;
                    line_as_string_stream >> box_max.z;

                    std::string box_material_name;
                    line_as_string_stream >> box_material_name;

                    std::shared_ptr<Material> box_material;

                    auto i = scene.material_cont.find(box_material_name);
                    if (i != scene.material_cont.end()) {
                        box_material = i->second;
                    }
                    else {
                        return;
                    }

                    std::shared_ptr<Shape> box = std::make_shared<Box>(Box{ box_name,box_material,
                                                                           box_min,box_max });

                    scene.shape_cont.try_emplace(box_name, box);
                }

                if ("sphere" == shape_object) {
                    std::string sphere_name;
                    line_as_string_stream >> sphere_name;

                    glm::vec3 sphere_center{ 0.0f,0.0f,0.0f };
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
                    }
                    else {
                        return;
                    }

                    std::shared_ptr<Shape> sphere = std::make_shared<Sphere>(Sphere{ sphere_name,sphere_material,
                                                                                    sphere_center,sphere_radius });

                    scene.shape_cont.try_emplace(sphere_name, sphere);
                }
            }

            if ("light" == object_string) {
                std::string light_name;
                line_as_string_stream >> light_name;

                glm::vec3 light_position{ 0.0f,0.0f,0.0f };
                line_as_string_stream >> light_position.x;
                line_as_string_stream >> light_position.y;
                line_as_string_stream >> light_position.z;

                Color light_color{ 0.0f,0.0f,0.0f };
                line_as_string_stream >> light_color.r;
                line_as_string_stream >> light_color.g;
                line_as_string_stream >> light_color.b;

                int light_brightness = 0;
                line_as_string_stream >> light_brightness;

                std::shared_ptr<Light> light = std::make_shared<Light>(Light{ light_position,light_color,
                                                                             light_brightness });
                scene.light_cont.try_emplace(light_name, light);
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

                Camera camera{ camera_angle, position, direction, up };

                scene.camera = std::make_pair(camera_name,camera);
            }
        }



        if ("transform" == token_string) {
            std::string object_name;
            line_as_string_stream >> object_name;

            std::string transform_type;
            line_as_string_stream >> transform_type;

            glm::mat4 translate_matrix;
            glm::mat4 rotation_matrix;
            glm::mat4 scale_matrix;
            glm::mat4 unit;
            
            // instantiate translate matrix
            if ("translate" == transform_type) {
                float translate_x = 0.0f;
                float translate_y = 0.0f;
                float translate_z = 0.0f;
                line_as_string_stream >> translate_x;
                line_as_string_stream >> translate_y;
                line_as_string_stream >> translate_z;

                translate_matrix = glm::translate(unit, { translate_x,translate_y,translate_z });
            }

            // instantiate rotation matrix
            if ("rotate" == transform_type) {
                float degree = 0.0f;
                line_as_string_stream >> degree;

                glm::vec3 rotation_axis = { 0.0f,0.0f,0.0f };
                line_as_string_stream >> rotation_axis.x;
                line_as_string_stream >> rotation_axis.y;
                line_as_string_stream >> rotation_axis.z;

                rotation_matrix = glm::rotate(degree, rotation_axis);
            }

            // instantiate scale matrix
            if ("scale" == transform_type) {
                float scale_x = 0.0f;
                float scale_y = 0.0f;
                float scale_z = 0.0f;
                line_as_string_stream >> scale_x;
                line_as_string_stream >> scale_y;
                line_as_string_stream >> scale_z;

                scale_matrix = glm::scale(unit, { scale_x,scale_y,scale_z });
            }

            glm::mat4 final_mat = translate_matrix * rotation_matrix * scale_matrix;

            auto shape_it = scene.shape_cont.find(object_name);

            if (shape_it != scene.shape_cont.end()) {
              shape_it->second->add_to_world_transformation(final_mat);
            }

            if (scene.camera.first == object_name) {
              scene.camera.second.add_to_world_transformation(final_mat);
            }
        }
    }

    in_sdf_file.close();
}

void SDFToolbox::clear_file(std::string const& file_path) {
    std::ofstream out_sdf_file(file_path, std::ofstream::out | std::ofstream::trunc);
    out_sdf_file.close();
}

void SDFToolbox::write_rot_animation(std::string const& filename, unsigned num_frames,
                                     std::string const& obj, float max_degree, glm::vec3 const& axes) {

  auto rotation_degree = max_degree / num_frames;
  std::ofstream out_sdf_file;
  out_sdf_file.open(filename, std::ios::app);

  auto x = std::to_string(axes.x);
  auto y = std::to_string(axes.y);
  auto z = std::to_string(axes.z);

  out_sdf_file << "transform " << obj << " rotate " << std::to_string(rotation_degree) << " " << x << " " << y << " " << z << "\n";

  out_sdf_file.close();
}

void SDFToolbox::write_trans_animation(std::string const& filename, unsigned num_frames,
                                        std::string const& obj, glm::vec3 const& translate) {


    std::ofstream out_sdf_file;
    out_sdf_file.open(filename, std::ios::app);

    auto trans_x = std::to_string(translate.x / num_frames);
    auto trans_y = std::to_string(translate.y / num_frames);
    auto trans_z = std::to_string(translate.z / num_frames);

    out_sdf_file << "transform " << obj << " translate " << trans_x << " " << trans_y << " " << trans_z << "\n";

    out_sdf_file.close();

}