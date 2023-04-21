#ifndef RAY_HPP
#define RAY_HPP

#include <glm/vec3.hpp>

struct Ray
{
  glm::vec3 origin = {0.0f, 0.0f, 0.0f};
  glm::vec3 direction = {0.0f, 0.0f, -1.0f};

  // set default refraction index to index of air
  float current_refraction_index = 1.0f;

  // recursion counter
  int counter = 0;
};


#endif // #ifndef RAY_HPP