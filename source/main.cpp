
#include "Shape.hpp"
#include "Sphere.hpp"
#include "Box.hpp"

#include <new>
void main() {


	Box box1 = { {0.0f,0.0f,0.0f} , {4.0f,2.0f,0.0f} };
	box1.print(std::cout);
	Sphere sphere1 = { {0.0f,0.0f,0.0f} , 4.2f , "Marvin" , {1.0f,1.0f,1.0f} };
	sphere1.print(std::cout);



	//5.8
	Color red{ 255,0,0 };
	glm::vec3 position{ 0.0f,0.0f,0.0f };

	Sphere* s1 = new Sphere{ position, 1.2f, "sphere0",red };
	Shape* s2 = new Sphere{ position, 1.2f, "sphere1", red };

	s1->print(std::cout);
	s2->print(std::cout);

	delete s1;
	delete s2;
}
