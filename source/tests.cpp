#define CATCH_CONFIG_RUNNER
#include <catch.hpp>

#include "Shape.hpp"
#include "Box.hpp"
#include "Sphere.hpp"

TEST_CASE("Task5.2", "[Task5.2]")
{
	Box box1 = { {0.0f,0.0f,0.0f} , {4.0f,2.0f,0.0f}};
	Box box2 = { {-6.9f,-4.0f,0.0f} , {6.9f,4.2f,1.3f}};

	// l = 4.0f , h = 2.0f , w = 0.0f
	REQUIRE(box1.area() == 16.0f); // 2*(4*0 + 4*2 + 0*2) = 16	(ist 2D)
	REQUIRE(box1.volume() == 0.0f); // 4 * 2 * 0 = 0			(ist 2D)

	// l = 13.8f , h = 8.2f , w = 1.3f
	REQUIRE(Approx(box2.area()) == 283.519f); // 2*(13.8*1.3 + 13.8*8.2 + 1.3*8.2)
	REQUIRE(Approx(box2.volume()) == 147.107f); // 13.8 * 8.2 * 1.3




	Sphere sphere1 = { {0.0f,0.0f,0.0f} , 4.2f};
	Sphere sphere2 = { {-2.4f, 6.9f,0.0f} , -1.3f};

	REQUIRE(Approx(sphere1.area()) == 221.67f); // 4 * pi * 4.2^2
	REQUIRE(Approx(sphere1.volume()) == 232.754f); // (4/3) * pi * 4.2^3

	REQUIRE(Approx(sphere2.area()) == 21.237f); //4 * pi * -1.3^2
	REQUIRE(Approx(sphere2.volume()) == 6.902f); // (4/3) * pi * -1.3^3

}

int main(int argc, char *argv[])
{
  return Catch::Session().run(argc, argv);
}
