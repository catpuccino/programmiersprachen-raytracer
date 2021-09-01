#include "application.hpp"
#include "parser.hpp"

Application::Application(Renderer const& renderer) :
        renderer_{renderer} {}


void Application::createCameraRotAnim(unsigned num_frames) {

  float degree_per_frame = 360.0f / num_frames;

  // initialize scene requisites
  Scene scene;
  SDFToolbox::parse_scene("D:/Nextcloud/Bauhaus Uni Weimar/SoSe_2021/Programmiersprachen/Belege/Beleg_6/materials.sdf",
                          scene);

  // create SDF file for each frame
  for (unsigned current_frame = 1; current_frame <= num_frames; ++current_frame) {

    if (current_frame == 2) {
      // write animation description in separate file
      SDFToolbox::write_scene(current_frame,"D:/Nextcloud/Bauhaus Uni Weimar/SoSe_2021/Programmiersprachen/Belege/Beleg_6/animation_description.txt",
                             degree_per_frame);
    }

    // apply animation step to existing scene
    SDFToolbox::parse_scene("D:/Nextcloud/Bauhaus Uni Weimar/SoSe_2021/Programmiersprachen/Belege/Beleg_6/animation_description.txt",
                           scene);
    renderer_.set_new_scene(scene);
    std::string filename = std::string("../../images/frame_") + std::to_string(current_frame) + ".ppm";
    renderer_.set_filename(filename);
    renderer_.render();
  }
}
