#define CATCH_CONFIG_RUNNER
#include "shape.hpp"
#include "sphere.hpp"
#include "box.hpp"
#include "scene.hpp"
#include "parser.hpp"
#include "renderer.hpp"
#include <catch.hpp>


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
  Box b{"Box",std::make_shared<Material>(Material{"Standard",
                                                  {0.5f,0.5f,0.5f},
                                                  {0.5f,0.5f,0.5f},
                                                  {0.5f,0.5f,0.5f},
                                                  2.0f}),
        {1.2f,3.2f,9.83f},{9.88f,2.3f,1.9f}};
  std::cout << b << std::endl;

  Sphere s{"Sphere",std::make_shared<Material>(Material{"Standard",
                                                        {0.5f,0.5f,0.5f},
                                                        {0.5f,0.5f,0.5f},
                                                        {0.5f,0.5f,0.5f},
                                                        2.0f}),
           {1.2f,3.2f,9.83f}};
  std::cout << s << std::endl;
}

TEST_CASE("intersect_ray_sphere", "[intersect]")
{
  // Tests with own intersect method
  Sphere s{"Katze",std::make_shared<Material>(Material{"Standard",
                                                       {0.5f,0.5f,0.5f},
                                                       {0.5f,0.5f,0.5f},
                                                       {0.5f,0.5f,0.5f},
                                                       2.0f}),
                                                       {0,1,-10}};
  HitPoint h = s.intersect(Ray{});
  REQUIRE(h.did_intersect == true);
  REQUIRE(h.distance == Approx(10));
  REQUIRE(h.name == "Katze");
  REQUIRE(h.hitpoint.z == -10);
  REQUIRE(h.hit_direction.x == 0);
  REQUIRE(h.hit_direction.y == 0);
  REQUIRE(h.hit_direction.z == -1);

  Sphere s0{"KATZE",std::make_shared<Material>(Material{"Standard",
                                                        {0.5f,0.5f,0.5f},
                                                        {0.5f,0.5f,0.5f},
                                                        {0.5f,0.5f,0.5f},
                                                        2.0f}),
                                                        {0,0,-10}};
  HitPoint h0 = s0.intersect(Ray{});
  REQUIRE(h0.did_intersect == true);
  REQUIRE(h0.distance == Approx(9));
  REQUIRE(h0.name == "KATZE");
  REQUIRE(h0.hitpoint.z == -9);
  REQUIRE(h0.hit_direction.x == 0);
  REQUIRE(h0.hit_direction.y == 0);
  REQUIRE(h0.hit_direction.z == -1);

  Sphere s1{"Katze123",std::make_shared<Material>(Material{"Standard",
                                                           {0.5f,0.5f,0.5f},
                                                           {0.5f,0.5f,0.5f},
                                                           {0.5f,0.5f,0.5f},
                                                           2.0f}),
                                                           {0,2,-10}};
  HitPoint h1 = s1.intersect(Ray{});
  REQUIRE(h1.did_intersect == false);
  REQUIRE(h1.distance == 0);
  REQUIRE(h1.name == "Katze123");
  REQUIRE(h1.hitpoint.x == 0);
  REQUIRE(h1.hitpoint.y == 0);
  REQUIRE(h1.hitpoint.z == 0);
  REQUIRE(h1.hit_direction.x == 0);
  REQUIRE(h1.hit_direction.y == 0);
  REQUIRE(h1.hit_direction.z == -1);
}

TEST_CASE("Box::intersect method", "[box_intersect]")
{
    Ray r;
    Box b_1{{-1.0f,-1.0f,-5.0f},{3.0f,5.0f,-10.0f}};
    auto hp = b_1.intersect(r);
    REQUIRE(hp.did_intersect == true);
    REQUIRE(hp.distance == 5);
    REQUIRE(hp.hitpoint.z == -5);

    Ray r1{{0,0,0},{-1,0.5f,1}};
    Box b_2{{-8.0f, 1.0f, 3.0f},{-1.0f, 6.0f, 6.0f}};
    auto hp_1 = b_2.intersect(r1);
    REQUIRE(hp_1.did_intersect == true);
    REQUIRE(hp_1.distance > 3);
    REQUIRE(hp_1.hitpoint.z == 3);

    Ray r2{{0,0,0},{0,-1,0.5f}};
    Box b_3{{-2,-8,0},{2,-3,5}};
    auto hp_2 = b_3.intersect(r2);
    REQUIRE(hp_2.did_intersect == true);
    REQUIRE(hp_2.distance > 3);
    REQUIRE(hp_2.hitpoint.y == -3);

    Ray r3{{0,0,0},{0,1,0}};
    Box  b_4{{1,1,1},{4,4,4}};
    auto hp_3 = b_4.intersect(r3);
    REQUIRE(hp_3.did_intersect == false);

  Ray ray = { glm::vec3{ 2.58f, 2.36f, 0.0f }, glm::vec3{ -4.64f, -2.28f, 2.0f } };
  Box b_5 = {{0.0f,0.0f,0.0f},{2.0f,2.0f,2.0f}};
  auto hitpoint = b_5.intersect(ray);
  REQUIRE(hitpoint.did_intersect == true);
  REQUIRE(hitpoint.name == "Box");
  REQUIRE(hitpoint.hit_direction.x == Approx(-0.836f).epsilon(0.01));
  REQUIRE(hitpoint.hit_direction.y == Approx(-0.412f).epsilon(0.01));
  REQUIRE(hitpoint.hit_direction.z == Approx(0.360f).epsilon(0.01));
  REQUIRE(hitpoint.distance == Approx(0.873f).epsilon(0.01));
  REQUIRE(hitpoint.hitpoint.x == Approx(1.847f).epsilon(0.01));
  REQUIRE(hitpoint.hitpoint.y == Approx(2.0f));
  REQUIRE(hitpoint.hitpoint.z == Approx(0.3158f).epsilon(0.01));
}

TEST_CASE("parse should read sdf file and create and add new materials to scene","[parse]")
{
  Scene s;

  SDFParser::parse_objects("D:/Nextcloud/Bauhaus Uni Weimar/SoSe_2021/Programmiersprachen/Belege/Beleg_6/materials.sdf",s);

}

TEST_CASE("testing compute_eye_ray", "[compute_eye_ray]")
{
  Camera camera{45.0f};

  Ray eye_ray = camera.compute_eye_ray(Pixel{1,3});
  REQUIRE(eye_ray.direction.x == Approx(0.169f).epsilon(0.001f));
}

int main(int argc, char *argv[])
{
  return Catch::Session().run(argc, argv);
}
