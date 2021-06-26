#include "Shape.hpp"
#include "Sphere.hpp"
#include "Box.hpp"

void main() {
	Box box1 = { {0.0f,0.0f,0.0f} , {4.0f,2.0f,0.0f} };
	box1.print(std::cout);
	Sphere sphere1 = { {0.0f,0.0f,0.0f} , {4.2f} , "Marvin" , {1.0f,1.0f,1.0f} };
	sphere1.print(std::cout);
	
}