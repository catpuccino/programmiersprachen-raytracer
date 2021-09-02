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
  unsigned const image_width = 800;
  unsigned const image_height = 600;
  std::string const filename = "../../rendered_image.ppm";
  std::string t_sdf_filepath{"D:/Ernst des Lebens/Uni/Informatik/Semester 2/Programmiersprachen/Uebung/Raytracer/materials.sdf"};
  std::string h_sdf_filepath{ "D:/Nextcloud/Bauhaus Uni Weimar/SoSe_2021/Programmiersprachen/Belege/Beleg_6/materials.sdf" };
  std::string sdf_filepath{"../../sdf/scene.sdf"};
  std::string animation_filepath{ "../../sdf/animation_description.sdf" };

  unsigned const num_frames = 120;

  Scene scene;
  SDFToolbox::parse_scene(sdf_filepath,scene);

  Renderer renderer{image_width, image_height, filename, scene};
  
  Application app{renderer};

  // write animation description in separate file
  SDFToolbox::write_rot_animation(animation_filepath, num_frames, 360.0f, "origin", glm::vec3{ 1, 0, 0 });
  //SDFToolbox::write_rot_animation(animation_filepath, num_frames, -360.0f, "ground", glm::vec3{ 1, 0, 0 });

  // create animation files
  app.createAnimation(num_frames);
  
  
  

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
