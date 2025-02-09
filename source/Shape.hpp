#ifndef SHAPE_HPP
#define SHAPE_HPP

#include "color.hpp"

class Shape
{
public:
	Shape(std::string const& newname_, Color const& newcolor_); //5.3
	Shape();
	virtual ~Shape();					//-->Sphere und Box Destruktor: Die Methode mit dem Überschreibungsspezifierer
										//"override" hat keine Basisklassenmathoden überschrieben.

	virtual float area() const = 0;		//5.1 rein virtuell, daher existiert keine Implementierung!
	virtual float volume() const = 0;	//5.1

	virtual std::ostream& print(std::ostream& os) const; //5.4

protected:								//5.3 i set it to protected instead of public so that it can still be
	std::string name_;					//accessed from Box/Sphere but is also not completely public!
	Color color_;
};

std::ostream& operator<<(std::ostream& os, Shape const& s);


#endif