#define CATCH_CONFIG_RUNNER
#include "shape.hpp"
#include "sphere.hpp"
#include "box.hpp"
#include "scene.hpp"
#include "parser.hpp"
#include "renderer.hpp"
#include <catch.hpp>
#include <glm/glm.hpp>				//5.6
#include <glm/gtx/intersect.hpp>

#include "Shape.hpp"
#include "Box.hpp"
#include "Sphere.hpp"


TEST_CASE("Task5.2", "[Task5.2]")
{

	Box box1 = { {0.0f,0.0f,0.0f} , {4.0f,2.0f,0.0f} };
	Box box2 = { {-6.9f,-4.0f,0.0f} , {6.9f,4.2f,1.3f} };

	// l = 4.0f , h = 2.0f , w = 0.0f
	REQUIRE(box1.area() == 16.0f); // 2*(4*0 + 4*2 + 0*2) = 16	(ist 2D)
	REQUIRE(box1.volume() == 0.0f); // 4 * 2 * 0 = 0			(ist 2D)

	// l = 13.8f , h = 8.2f , w = 1.3f
	REQUIRE(Approx(box2.area()) == 283.519f); // 2*(13.8*1.3 + 13.8*8.2 + 1.3*8.2)
	REQUIRE(Approx(box2.volume()) == 147.107f); // 13.8 * 8.2 * 1.3




	Sphere sphere1 = { {0.0f,0.0f,0.0f} , 4.2f };
	Sphere sphere2 = { {-2.4f, 6.9f,0.0f} , -1.3f };

	REQUIRE(Approx(sphere1.area()) == 221.67f); // 4 * pi * 4.2^2
	REQUIRE(Approx(sphere1.volume()) == 232.754f); // (4/3) * pi * 4.2^3

	REQUIRE(Approx(sphere2.area()) == 21.237f); //4 * pi * -1.3^2
	REQUIRE(Approx(sphere2.volume()) == 6.902f); // (4/3) * pi * -1.3^3
}


//5.6
TEST_CASE("intersect_ray_sphere", "[intersect]")
{
	//Ray
	glm::vec3 ray_origin{ 0.0f,0.0f,0.0f };
	//ray direction has to be normalized!
	//you can use:
	// v = glm::normalize(some_vector)
	glm::vec3 ray_direction{ 0.0f,0.0f,1.0f };

	//sphere
	glm::vec3 sphere_center{ 0.0f,0.0f,5.0f };
	float sphere_radius{ 1.0f };
	float distance = 0.0f;
	auto result = glm::intersectRaySphere(
		ray_origin, ray_direction, sphere_center,
		sphere_radius * sphere_radius, //squard radius!!
		distance);
	REQUIRE(distance == Approx(4.0f));
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

  //Ray eye_ray = camera.compute_eye_ray(Pixel{1,1},200);
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

TEST_CASE("test transpose matrix","[tanspose]")
{
  glm::mat4 m = {{1,1,1,1},{0,0,0,0},{1,1,1,1},{0,0,0,0}};
  glm::mat4 m_t = glm::transpose(m);
}

int main(int argc, char *argv[])
{
  return Catch::Session().run(argc, argv);
}
