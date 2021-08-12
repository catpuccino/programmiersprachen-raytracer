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

  SDFParser::parse_scene("D:/Nextcloud/Bauhaus Uni Weimar/SoSe_2021/Programmiersprachen/Belege/Beleg_6/materials.sdf",s);

}

TEST_CASE("testing compute_eye_ray", "[compute_eye_ray]")
{
  Camera camera{45.0f};

  Ray eye_ray = camera.compute_eye_ray(Pixel{1,1},200);
  //REQUIRE(eye_ray.direction.x == Approx(1).epsilon(0.001f)); //not working
}

TEST_CASE("testing Sphere::normal()", "[Sphere::normal()]")
{
    Sphere s = { {0.0f, 0.0f, 0.0f}, 4.54f };
    HitPoint hp = { TRUE,  3.0f, "Test",
        std::make_shared<Material>(Material{"Standard", {0.5f,0.5f,0.5f}, {0.5f,0.5f,0.5f},
                                                        {0.5f,0.5f,0.5f}, 2.0f}),
        {1.15f, 2.65f, 3.5f}, {0.0f, 1.0f, -1.0f} };

    auto norm = s.create_normal(hp);
    REQUIRE(norm.x == Approx(0.253f).epsilon(0.01f));
    REQUIRE(norm.y == Approx(0.584f).epsilon(0.01f));
    REQUIRE(norm.z == Approx(0.771f).epsilon(0.01f));


    Sphere s2 = { {2.0f, 3.0f, -3.0f}, 2.95f };
    hp = { TRUE,  3.0f, "Test2",
        std::make_shared<Material>(Material{"Standard", {0.5f,0.5f,0.5f}, {0.5f,0.5f,0.5f},
                                                        {0.5f,0.5f,0.5f}, 2.0f}),
        {4.15f, 1.65f, -1.5f}, {0.0f, 1.0f, -1.0f} };

    norm = s2.create_normal(hp);
    REQUIRE(norm.x == Approx(0.729f).epsilon(0.001f));
    REQUIRE(norm.y == Approx(-0.458f).epsilon(0.001f));
    REQUIRE(norm.z == Approx(0.509f).epsilon(0.001f));
}

TEST_CASE("testing Box::normal()", "[Box::normal()]")
{
    Box b = { {0.0f, 0.0f, 0.0f}, {10.0f, 10.0f, 10.0f} };
    Ray r = { {13.59f, -12.49, -4.2 }, {-27.4f, 33.12f, 9.5f} };

    HitPoint hp = b.intersect(r);
    auto norm = b.create_normal(hp);

    REQUIRE(norm.x == Approx(0.0f));
    REQUIRE(norm.y == Approx(0.0f));
    REQUIRE(norm.z == Approx(1.0f));


    b = { {3.0f, 1.0f, 5.0f}, {10.0f, 8.0f, 12.0f} };
    r = { {15.59f, -12.49, 27.3 }, {-23.4f, 33.12f, -31.6f} };

    hp = b.intersect(r);
    norm = b.create_normal(hp);

    REQUIRE(norm.x == Approx(0.0f));
    REQUIRE(norm.y == Approx(0.0f));
    REQUIRE(norm.z == Approx(1.0f));
}


TEST_CASE("testing Renderer::trace_ray()", "[Renderer::trace_ray()]")
{
    Scene s;

    auto b1 = std::make_pair<std::string, std::shared_ptr<Box>>
        (std::string{ "b1" },
         std::make_shared<Box>(glm::vec3{-19.0f, -11.0f, 0.0f}, glm::vec3{-12.0f, -4.0f, 7.0f}));
    auto b2 = std::make_pair<std::string, std::shared_ptr<Box>>
        (std::string{ "b2" },
            std::make_shared<Box>(glm::vec3{ 2.0f, -12.0f, 0.0f }, glm::vec3{ 8.0f, -6.0f, 6.0f }));
    auto s1 = std::make_pair<std::string, std::shared_ptr<Sphere>>
        (std::string{ "s1" },
            std::make_shared<Sphere>(glm::vec3{ 8.0f, 3.1f, 4.3f }, 4.49f));
    auto s2 = std::make_pair<std::string, std::shared_ptr<Sphere>>
        (std::string{ "s2" },
            std::make_shared<Sphere>(glm::vec3{ -8.0f, 6.2f, -5.1f }, 5.1f));

    s.shape_cont.emplace(b1);
    s.shape_cont.emplace(b2);
    s.shape_cont.emplace(s1);
    s.shape_cont.emplace(s2);

    Renderer renderer = { 20, 20, "Renderer", s };
    
    Ray r1 = { {-6.4f, -17.0f, -12.4f }, {8.9f, 30.3f, 16.63f} };

    auto test_tracing = renderer.trace_ray(r1);

    // Ray should not hit
    REQUIRE(test_tracing.r == Approx(0.85f));
    REQUIRE(test_tracing.g == Approx(0.85f));
    REQUIRE(test_tracing.b == Approx(0.85f));

    Ray r2 = { {18.9f, -20.9f, 10.0f }, {-23.2f, 27.6f, -12.0f} };

    test_tracing = renderer.trace_ray(r2);

    // Ray should hit -- TEST WILL NOT WORK ONCE shade() HAS BEEN IMPLEMENTED --
    //REQUIRE(test_tracing.r == Approx(0.5f));
    //REQUIRE(test_tracing.g == Approx(0.5f));
    //REQUIRE(test_tracing.b == Approx(0.5f));

}


int main(int argc, char *argv[])
{
  return Catch::Session().run(argc, argv);
}
