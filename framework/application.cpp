#include "application.hpp"
#include "parser.hpp"

Application::Application(Renderer const& renderer) :
        renderer_{renderer} {}


void Application::createAnimation(unsigned num_frames) {

  // initialize scene requisites
  Scene scene;
  SDFToolbox::parse_scene("../../sdf/scene.sdf",
                          scene);

  // create SDF file for each frame
  for (unsigned current_frame = 1; current_frame <= num_frames; ++current_frame) {

    if (current_frame >= 2) {
        // apply animation step to existing scene
        SDFToolbox::parse_scene("../../sdf/animation_description.sdf", scene);
        renderer_.set_new_scene(scene);

    }
    std::string filename = std::string("../../images/frame_") + std::to_string(current_frame) + ".ppm";
    renderer_.set_filename(filename);
    renderer_.render();
  }
}
