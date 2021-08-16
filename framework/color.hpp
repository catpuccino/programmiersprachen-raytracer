// -----------------------------------------------------------------------------
// Copyright  : (C) 2014-2017 Andreas-C. Bernstein
// License    : MIT (see the file LICENSE)
// Maintainer : Andreas-C. Bernstein <andreas.bernstein@uni-weimar.de>
// Stability  : experimental
//
// Color
// -----------------------------------------------------------------------------

#ifndef BUW_COLOR_HPP
#define BUW_COLOR_HPP

#include <iostream>

struct Color
{

  friend std::ostream& operator<<(std::ostream& os, Color const& c)
  {
    os << "(" << c.r << "," << c.g << "," << c.b << ")\n";
    return os;
  }

  Color& operator+=(Color const& other)
  {
    r += other.r;
    g += other.g;
    b += other.b;
    return *this;
  }

  Color& operator-=(Color const& other)
  {
    r -= other.r;
    g -= other.g;
    b -= other.b;
    return *this;
  }

  Color& operator*=(Color const& other)
  {
      r *= other.r;
      g *= other.g;
      b *= other.b;
      return *this;
  }

  Color& operator*=(float v)
  {
      r *= v;
      g *= v;
      b *= v;
      return *this;
  }

  Color& operator*=(int v)
  {
      r *= v;
      g *= v;
      b *= v;
      return *this;
  }

  friend Color operator+(Color const& a, Color const& b)
  {
    auto tmp(a);
    tmp += b;
    return tmp;
  }

  friend Color operator-(Color const& a, Color const& b)
  {
    auto tmp(a);
    tmp -= b;
    return tmp;
  }

  friend Color operator*(Color const& a, Color const& b)
  {
      auto tmp(a);
      tmp *= b;
      return tmp;
  }

  friend Color operator*(Color const& c, float v)
  {
      auto tmp(c);
      tmp *= v;
      return tmp;
  }

  friend Color operator*(float v, Color const& c)
  {
      return c * v;
  }

  friend Color operator*(Color const& c, int v)
  {
      auto tmp(c);
      tmp *= v;
      return tmp;
  }

  friend Color operator*(int v, Color const& c)
  {
      return c * v;
  }

  Color operator+(float i)
  {
    Color temp;
    r += i;
    g += i;
    b += i;
    return *this;
  }

  Color& operator/(Color const& other)
  {
    r /= other.r;
    g /= other.g;
    b /= other.b;
    return *this;
  }

  float r;
  float g;
  float b;
};

#endif //#define BUW_COLOR_HPP
