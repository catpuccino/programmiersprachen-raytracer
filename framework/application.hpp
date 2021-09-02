#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include "parser.hpp"
#include "renderer.hpp"

class Application {
  public:
    Application(Renderer const& renderer);
    void createAnimation(unsigned num_frames);
  private:
    Renderer renderer_;
};



#endif // APPLICATION_HPP