#ifndef SHAPE_HPP
#define SHAPE_HPP

#include "color.hpp"
#include "window.hpp"

class Shape
{
public:
	virtual float area() const = 0;		//5.1 rein virtuell, daher existiert keine Implementierung!
	virtual float volume() const = 0;	//5.1
};

#endif