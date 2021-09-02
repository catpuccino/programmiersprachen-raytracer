#include "application.hpp"
#include "parser.hpp"

Application::Application(Renderer const& renderer) :
        renderer_{renderer} {}


void Application::createRotationAnim(unsigned num_frames, float max_degree, std::string const& obj_name, glm::vec3 const& axes) {

  float degree_per_frame = max_degree / num_frames;

  // initialize scene requisites
  Scene scene;
  SDFToolbox::parse_scene("../../source/scene.sdf",
                          scene);

  // create SDF file for each frame
  for (unsigned current_frame = 1; current_frame <= num_frames; ++current_frame) {

    if (current_frame == 2) {
      // write animation description in separate file
      SDFToolbox::write_animation("D:/Ernst des Lebens/Uni/Informatik/Semester 2/Programmiersprachen/Uebung/Raytracer/animation_description.txt",
            obj_name, degree_per_frame, axes);
    }

    // apply animation step to existing scene
    SDFToolbox::parse_scene("D:/Ernst des Lebens/Uni/Informatik/Semester 2/Programmiersprachen/Uebung/Raytracer/animation_description.txt",
                           scene);
    renderer_.set_new_scene(scene);
    std::string filename = std::string("../../images/frame_") + std::to_string(current_frame) + ".ppm";
    renderer_.set_filename(filename);
    renderer_.render();
  }
}
