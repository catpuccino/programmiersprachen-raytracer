#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include "parser.hpp"
#include "renderer.hpp"

class Application {
  public:
    Application(Renderer const& renderer);
    void createRotationAnim(unsigned num_frames, float max_degree, std::string const& obj_name, glm::vec3 const& axes);
  private:
    Renderer renderer_;
};



#endif // APPLICATION_HPP