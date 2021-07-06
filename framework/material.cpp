#include "material.hpp"

std::ostream& operator<<(std::ostream& os, Material const& material) {
  os << "Mat-Name: " << material.name_ << std::endl;
  os << "ka: " << material.ka << std::endl;
  os << "kd: " << material.kd << std::endl;
  os << "ks: " << material.ks << std::endl;
  os << "m: " << material.m << std::endl;
  return os;
}