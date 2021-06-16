#define CATCH_CONFIG_RUNNER
#include <catch.hpp>
#include "shape.hpp"
#include "sphere.hpp"
#include "box.hpp"

TEST_CASE("Testing area and volume methods on Sphere and Box objects", "[area&volume]")
{
  Sphere s{{1.f,2.f,34.f}};
  float es = s.area();

  REQUIRE(es > 1);
}

int main(int argc, char *argv[])
{
  return Catch::Session().run(argc, argv);
}
