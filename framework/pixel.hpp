// -----------------------------------------------------------------------------
// Copyright  : (C) 2014-2017 Andre Schollmeyer and Andreas-C. Bernstein
// License    : MIT (see the file LICENSE)
// Maintainer : Andreas-C. Bernstein <andreas.bernstein@uni-weimar.de>
// Stability  : experimental
//
// Pixel
// -----------------------------------------------------------------------------

#ifndef BUW_PIXEL_HPP
#define BUW_PIXEL_HPP

// header, system
#include <iosfwd>

// header, project
#include <color.hpp>

class Pixel
{
public :

  Pixel(float = 0.0f, float = 0.0f);
  void print(std::ostream&) const;

  float x = 0;
  float y = 0;
  Color color = {1.0, 1.0, 1.0};
};

std::ostream& operator<<(std::ostream&, const Pixel&);

#endif // BUW_PIXEL_HPP
