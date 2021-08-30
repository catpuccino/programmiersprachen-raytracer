#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include "renderer.hpp"

class Application {
  public:
    Application(Renderer const& renderer);
    void createCameraRotAnim(unsigned num_frames);
  private:
    Renderer renderer_;
};



#endif // APPLICATION_HPP