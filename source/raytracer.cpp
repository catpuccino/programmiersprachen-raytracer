#include <parser.hpp>
#include <renderer.hpp>
#include <application.hpp>
#include <window.hpp>

#include <GLFW/glfw3.h>
#include <thread>
#include <utility>
#include <cmath>
#include <string>

//now single threaded again
int main(int argc, char* argv[])
{
  unsigned const image_width = 1200;
  unsigned const image_height = 1000;
  std::string const filename = "../../images/rendered_image.ppm";
  std::string t_sdf_filepath{"D:/Ernst des Lebens/Uni/Informatik/Semester 2/Programmiersprachen/Uebung/Raytracer/materials.sdf"};
  std::string h_sdf_filepath{ "D:/Nextcloud/Bauhaus Uni Weimar/SoSe_2021/Programmiersprachen/Belege/Beleg_6/scene.sdf" };
  std::string sdf_filepath{"../../sdf/scene.sdf"};
  std::string animation_filepath{ "../../sdf/animation_description.sdf" };


  unsigned const num_frames = 450;

  Scene scene;
  SDFToolbox::parse_scene(sdf_filepath,scene);

  Renderer renderer{image_width, image_height, filename, scene};

  Application app{renderer};

  SDFToolbox::clear_file(animation_filepath);

  // write animation description in separate file

  //SDFToolbox::write_rot_animation(animation_filepath, num_frames, "origin", 360.0f, glm::vec3{ 0, 1, 0 });
  //SDFToolbox::write_rot_animation(animation_filepath, num_frames, "boxi", 180.0f, glm::vec3{ 0, 1, 0 });

  SDFToolbox::write_trans_animation(animation_filepath, num_frames, "origin", glm::vec3{ 0, 14, 0 });
  //SDFToolbox::write_trans_animation(animation_filepath, num_frames, "refract_box", glm::vec3{ 0, 5, 0 });
  //SDFToolbox::write_trans_animation(animation_filepath, num_frames, "rund", glm::vec3{ 0, 10, 0 });
  //SDFToolbox::write_trans_animation(animation_filepath, num_frames, "kugel", glm::vec3{ -9, 0, 15 });

  app.createAnimation(num_frames, 1);




  // CODE F�R KAMERAFAHRTEN
  // write if-statement for each seperate movement you want
  // numbers that are compared in the if statement are start and end frame of this animation
  // insert total length of animation (end-start) as second argument in write_rot_animation Method
    /*
  for (auto current_frame = 1; current_frame <= num_frames; ++current_frame) {
    
    SDFToolbox::clear_file(animation_filepath);
    if (2 <= current_frame && current_frame <= 110) {
      SDFToolbox::write_rot_animation(animation_filepath, 108, "front", 268.0f, glm::vec3{ 0, 1, 0 });
    }

    if (2 <= current_frame && current_frame <= 56) {
        SDFToolbox::write_trans_animation(animation_filepath, 54, "front",glm::vec3{ 0, 7, 0 });
    }

    if (58 <= current_frame && current_frame <= 110) {
        SDFToolbox::write_trans_animation(animation_filepath, 52, "front", glm::vec3{ 0, -3, 0 });
    }

    if (120 <= current_frame && current_frame <= 180) {
        SDFToolbox::write_trans_animation(animation_filepath, 60, "glass_sphere", glm::vec3{ 0, -15, 0 });
    }

    if (120 <= current_frame && current_frame <= 240) {
        SDFToolbox::write_trans_animation(animation_filepath, 120, "front", glm::vec3{ 18, 0, 0 });
    }
   
    SDFToolbox::parse_scene("../../sdf/animation_description.sdf",
                                scene);
    renderer.set_new_scene(scene);

    std::string filename = std::string("../../images/frame_") + std::to_string(current_frame) + ".ppm";
    renderer.set_filename(filename);

    renderer.render();
  }
    */


  
  //renderer.render();


  Window window{{image_width, image_height}};

  while (!window.should_close()) {
    if (window.get_key(GLFW_KEY_ESCAPE) == GLFW_PRESS) {
      window.close();
    }
    window.show(renderer.color_buffer());
  }

  return 0;
}
