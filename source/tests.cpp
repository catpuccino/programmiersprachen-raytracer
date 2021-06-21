#define CATCH_CONFIG_RUNNER
#include <catch.hpp>
#include "shape.hpp"
#include "sphere.hpp"
#include "box.hpp"

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

int main(int argc, char *argv[])
{
  return Catch::Session().run(argc, argv);
}
