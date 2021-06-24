#define CATCH_CONFIG_RUNNER
#include "shape.hpp"
#include "sphere.hpp"
#include "box.hpp"
#include <catch.hpp>
#include <glm/glm.hpp>
#include <glm/gtx/intersect.hpp>

TEST_CASE("Testing area and volume methods on Sphere and Box objects", "[area&volume]")
{
  SECTION("Sphere area")
  {
    Sphere s{{1.0f,1.0f,1.0f},4.0f};
    REQUIRE(Approx(201.06f) == s.area());

    Sphere s1{{1.0f,1.0f,1.0f},0.0f};
    REQUIRE(0 == s1.area());

    Sphere s2{{1.0f,1.0f,1.0f},1.0f};
    REQUIRE(Approx(12.57f).epsilon(0.01) == s2.area());
  }

  SECTION("Sphere volume")
  {
    Sphere s{{1.0f,1.0f,1.0f},4.0f};
    REQUIRE(Approx(268.08f) == s.volume());

    Sphere s1{{1.0f,1.0f,1.0f},0.0f};
    REQUIRE(0 == s1.volume());

    Sphere s2{{1.0f,1.0f,1.0f},1.0f};
    REQUIRE(Approx(4.19f).epsilon(0.01) == s2.volume());
  }

  SECTION("Box area")
  {
    Box b{{0.0f,0.0f,0.0f},{0.0f,0.0f,0.0f}};
    REQUIRE(0 == b.area());

    Box b1{{1.0f,1.0f,1.0f},{3.0f,3.0f,3.0f}};
    REQUIRE(24 == b1.area());

    Box b3{{-2.0f,1.0f,2.0f},{3.0f,3.0f,6.0f}};
    REQUIRE(76 == b3.area());
  }

  SECTION("Box volume")
  {
    Box b{{0.0f,0.0f,0.0f},{0.0f,0.0f,0.0f}};
    REQUIRE(0 == b.volume());

    Box b1{{1.0f,1.0f,1.0f},{3.0f,3.0f,3.0f}};
    REQUIRE(8 == b1.volume());

    Box b2{{-2.0f,1.0f,2.0f},{3.0f,3.0f,2.0f}};
    REQUIRE(0 == b2.volume());

    Box b4{{-2.0f,1.0f,2.0f},{3.0f,3.0f,6.0f}};
    REQUIRE(40 == b4.volume());
  }
}

TEST_CASE("print method should print all member attributes of each class to the console", "[print]")
{
  Box b{"Box",{0.2f,0.1f,0.3f},{1.2f,3.2f,9.83f},{9.88f,2.3f,1.9f}};
  std::cout << b << std::endl;

  Sphere s{"Sphere",{0.2f,0.1f,0.3f},{1.2f,3.2f,9.83f}};
  std::cout << s << std::endl;
}

TEST_CASE("intersect_ray_sphere", "[intersect]")
{
// Ray
  glm::vec3 ray_origin{0.0f,0.0f,0.0f};
// ray direction has to be normalized !
// you can use :
// v = glm::normalize(some_vector)
  glm::vec3 ray_direction{0.0f,0.0f,1.0f};
// Sphere
  glm::vec3 sphere_center{0.0f, 0.0f, 5.0f};
  float sphere_radius{1.0f};
  float distance = 0.0f;
  auto result = glm::intersectRaySphere(
          ray_origin , ray_direction,
          sphere_center,
          sphere_radius * sphere_radius, // squared radius !!!
          distance);
  REQUIRE(distance == Approx(4.0f));

  // Tests with own intersect method
  Sphere s{"Katze",{0.5f,0.5f,0.5f},{0,1,-10}};
  HitPoint h = s.intersect(Ray{});
  REQUIRE(h.did_intersect == true);
  REQUIRE(h.t == Approx(10));
  REQUIRE(h.name == "Katze");
  REQUIRE(h.color.r == 0.5f);
  REQUIRE(h.color.g == 0.5f);
  REQUIRE(h.color.b == 0.5f);
  REQUIRE(h.hitpoint.z == -10);
  REQUIRE(h.hit_direction.x == 0);
  REQUIRE(h.hit_direction.y == 0);
  REQUIRE(h.hit_direction.z == -1);

  Sphere s0{"KATZE",{0.5f,0.5f,0.5f},{0,0,-10}};
  HitPoint h0 = s0.intersect(Ray{});
  REQUIRE(h0.did_intersect == true);
  REQUIRE(h0.t == Approx(9));
  REQUIRE(h0.name == "KATZE");
  REQUIRE(h0.color.r == 0.5f);
  REQUIRE(h0.color.g == 0.5f);
  REQUIRE(h0.color.b == 0.5f);
  REQUIRE(h0.hitpoint.z == -9);
  REQUIRE(h0.hit_direction.x == 0);
  REQUIRE(h0.hit_direction.y == 0);
  REQUIRE(h0.hit_direction.z == -1);

  Sphere s1{"Katze123",{0.1f,0.1f,0.1f},{0,2,-10}};
  HitPoint h1 = s1.intersect(Ray{});
  REQUIRE(h1.did_intersect == false);
  REQUIRE(h1.t == 0);
  REQUIRE(h1.name == "Katze123");
  REQUIRE(h1.color.r == 0.1f);
  REQUIRE(h1.color.g == 0.1f);
  REQUIRE(h1.color.b == 0.1f);
  REQUIRE(h1.hitpoint.x == 0);
  REQUIRE(h1.hitpoint.y == 0);
  REQUIRE(h1.hitpoint.z == 0);
  REQUIRE(h1.hit_direction.x == 0);
  REQUIRE(h1.hit_direction.y == 0);
  REQUIRE(h1.hit_direction.z == -1);
}

TEST_CASE("order of con- and destructors of class hierarchy", "[hierarchy]")
{
  std::cout << "\n=========================\n" << std::endl;
  Color red{255, 0, 0};
  glm::vec3 position{0.0f, 0.0f, 0.0f};
  Sphere * s1 = new Sphere{"sphere0", red, position, 1.2f};
  Shape * s2 = new Sphere{"sphere1", red, position, 1.2f};
  s1->print(std::cout);
  s2->print(std::cout);
  delete s1;
  delete s2;
}

int main(int argc, char *argv[])
{
  return Catch::Session().run(argc, argv);
}
