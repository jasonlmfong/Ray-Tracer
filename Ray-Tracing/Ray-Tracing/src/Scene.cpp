#include "Scene.h"

Scene::Scene()
	:
	m_Camera(Vec3(0.0, 0.0, 0.0),
		Vec3(0.0, 0.0, -1.0),
		Vec3(0.0, 1.0, 0.0),
		60.0,
		16.0 / 9.0,
		0.1,
		(Vec3(0.0, 0.0, 0.0) - Vec3(0.0, 0.0, -1.0)).Length(),
		0.0,
		1.0
	)
{}

// scene near end of "one weekend"
void Scene::BuildScene1() {
	// world
	HittableList world;
	m_Background = Color(0.70, 0.80, 1.00);

	auto material_ground = make_shared<Lambertian>(Color(0.8, 0.8, 0.0));
	auto material_center = make_shared<Lambertian>(Color(0.7, 0.3, 0.3));
	auto material_front	 = make_shared<Lambertian>(Color(0.1, 0.2, 0.5));
	auto material_left	 = make_shared<Dielectric>(1.5);
	auto material_right  = make_shared<Metal>(Color(0.8, 0.6, 0.2), 1.0);

	world.Add(make_shared<Sphere>(Point3(0.0, -100.5, -1.0), 100.0, material_ground));
	world.Add(make_shared<Sphere>(Point3(0.0, 0.0, -1.5), 0.5, material_center));
	world.Add(make_shared<Sphere>(Point3(0.0, 0.0, -0.5), 0.5, material_front));
	world.Add(make_shared<Sphere>(Point3(-1.0, 0.0, -2.0), 0.5, material_left));
	world.Add(make_shared<Sphere>(Point3(-1.0, 0.0, -2.0), -0.45, material_left)); //glass ball with thickness
	world.Add(make_shared<Sphere>(Point3(1.0, 0.0, -1.0), 0.5, material_right));

	m_World = world;

	// camera
	Point3 lookfrom(-2, 2, 1);
	Point3 lookat(0, 0, -1.5);
	Vec3 vup(0, 1, 0);
	auto dist_to_focus = (lookfrom - lookat).Length();
	auto aperture = 0.5; // adjust depth of field 
	m_AspectRatio = 16.0 / 9.0;

	Camera cam(lookfrom, lookat, vup, 45, m_AspectRatio, aperture, dist_to_focus, 0, 0);

	m_Camera = cam;
}

// cover scene of "one weekend"
void Scene::BuildScene2() {
	// world
	HittableList world;
	m_Background = Color(0.70, 0.80, 1.00);

	auto ground_material = make_shared<Lambertian>(Color(0.5, 0.5, 0.5));
	world.Add(make_shared<Sphere>(Point3(0, -1000, 0), 1000, ground_material));

	for (int a = -11; a < 11; a++) {
		for (int b = -11; b < 11; b++) {
			auto choose_mat = RandomDouble();
			Point3 center(a + 0.9 * RandomDouble(), 0.2, b + 0.9 * RandomDouble());

			if ((center - Point3(4, 0.2, 0)).Length() > 0.9) {
				shared_ptr<Material> Sphere_material;

				if (choose_mat < 0.8) {
					// diffuse
					auto albedo = RandomVec3() * RandomVec3();
					Sphere_material = make_shared<Lambertian>(albedo);
					world.Add(make_shared<Sphere>(center, 0.2, Sphere_material));
				}
				else if (choose_mat < 0.95) {
					// metal
					auto albedo = RandomVec3(0.5, 1);
					auto fuzz = RandomDouble(0, 0.5);
					Sphere_material = make_shared<Metal>(albedo, fuzz);
					world.Add(make_shared<Sphere>(center, 0.2, Sphere_material));
				}
				else {
					// glass
					Sphere_material = make_shared<Dielectric>(1.5);
					world.Add(make_shared<Sphere>(center, 0.2, Sphere_material));
				}
			}
		}
	}

	auto material1 = make_shared<Dielectric>(1.5);
	world.Add(make_shared<Sphere>(Point3(0, 1, 0), 1.0, material1));

	auto material2 = make_shared<Lambertian>(Color(0.4, 0.2, 0.1));
	world.Add(make_shared<Sphere>(Point3(-4, 1, 0), 1.0, material2));

	auto material3 = make_shared<Metal>(Color(0.7, 0.6, 0.5), 0.0);
	world.Add(make_shared<Sphere>(Point3(4, 1, 0), 1.0, material3));

	m_World = world;

	// camera
	Point3 lookfrom(13, 2, 3);
	Point3 lookat(0, 0, 0);
	Vec3 vup(0, 1, 0);
	auto dist_to_focus = 10.0;
	auto aperture = 0.1;
	m_AspectRatio = 16.0 / 9.0;

	Camera cam(lookfrom, lookat, vup, 20, m_AspectRatio, aperture, dist_to_focus, 0, 0);

	m_Camera = cam;
}

// "next week" bouncing balls with checkered ground
void Scene::BuildScene3() {
	// world
	HittableList world;
	m_Background = Color(0.70, 0.80, 1.00);

	shared_ptr<Texture> checker = make_shared<CheckerTexture>(Color(1.0, 0.0, 1.0), Color(0.0, 0.0, 0.0));
	world.Add(make_shared<Sphere>(Point3(0, -1000, 0), 1000, make_shared<Lambertian>(checker)));

	for (int a = -11; a < 11; a++) {
		for (int b = -11; b < 11; b++) {
			auto choose_mat = RandomDouble();
			Point3 center(a + 0.9 * RandomDouble(), 0.2, b + 0.9 * RandomDouble());

			if ((center - Point3(4, 0.2, 0)).Length() > 0.9) {
				shared_ptr<Material> Sphere_material;

				if (choose_mat < 0.8) {
					// diffuse
					auto albedo = RandomVec3() * RandomVec3();
					Sphere_material = make_shared<Lambertian>(albedo);
					auto center2 = center + Vec3(0, RandomDouble(0, .5), 0);
					world.Add(make_shared<MovingSphere>(center, center2, 0.0, 1.0, 0.2, Sphere_material));
				}
				else if (choose_mat < 0.95) {
					// metal
					auto albedo = RandomVec3(0.5, 1);
					auto fuzz = RandomDouble(0, 0.5);
					Sphere_material = make_shared<Metal>(albedo, fuzz);
					world.Add(make_shared<Sphere>(center, 0.2, Sphere_material));
				}
				else {
					// glass
					Sphere_material = make_shared<Dielectric>(1.5);
					world.Add(make_shared<Sphere>(center, 0.2, Sphere_material));
				}
			}
		}
	}

	auto material1 = make_shared<Dielectric>(1.5);
	world.Add(make_shared<Sphere>(Point3(0, 1, 0), 1.0, material1));

	auto material2 = make_shared<Lambertian>(Color(0.4, 0.2, 0.1));
	world.Add(make_shared<Sphere>(Point3(-4, 1, 0), 1.0, material2));

	auto material3 = make_shared<Metal>(Color(0.7, 0.6, 0.5), 0.0);
	world.Add(make_shared<Sphere>(Point3(4, 1, 0), 1.0, material3));

	m_World = world;

	// camera
	Point3 lookfrom(13, 2, 3);
	Point3 lookat(0, 0, 0);
	Vec3 vup(0, 1, 0);
	auto dist_to_focus = 10.0;
	auto aperture = 0.1;
	m_AspectRatio = 16.0 / 9.0;

	Camera cam(lookfrom, lookat, vup, 20, m_AspectRatio, aperture, dist_to_focus, 0.0, 1.0);

	m_Camera = cam;
}

// "next week" two checkered spheres scene
void Scene::BuildScene4() {
	// world
	HittableList world;
	m_Background = Color(0.70, 0.80, 1.00);

	auto checker = make_shared<CheckerTexture>(Color(1.0, 0.0, 1.0), Color(0.0, 0.0, 0.0));

	world.Add(make_shared<Sphere>(Point3(0, -10, 0), 10, make_shared<Lambertian>(checker)));
	world.Add(make_shared<Sphere>(Point3(0, 10, 0), 10, make_shared<Lambertian>(checker)));

	m_World = world;

	// camera
	Point3 lookfrom(13, 2, 3);
	Point3 lookat(0, 0, 0);
	Vec3 vup(0, 1, 0);
	auto dist_to_focus = 10.0;
	auto aperture = 0.1;
	m_AspectRatio = 16.0 / 9.0;

	Camera cam(lookfrom, lookat, vup, 20, m_AspectRatio, aperture, dist_to_focus, 0.0, 1.0);

	m_Camera = cam;
}

// "next week" 3 perlin spheres scene (not same sized)
void Scene::BuildScene5() {
	// world
	HittableList world;
	m_Background = Color(0.70, 0.80, 1.00);

	auto smoothPerText = make_shared<SmoothNoiseTexture>(4); // new perlin noise marble textures

	world.Add(make_shared<Sphere>(Point3(0, -1000, 0), 1000, make_shared<Lambertian>(smoothPerText)));
	world.Add(make_shared<Sphere>(Point3(1, 2.5, -2), 2, make_shared<Lambertian>(smoothPerText)));
	world.Add(make_shared<Sphere>(Point3(-1, 1, 2), 2, make_shared<Lambertian>(smoothPerText)));

	m_World = world;

	// camera
	Point3 lookfrom(13, 2, 3);
	Point3 lookat(0, 0, 0);
	Vec3 vup(0, 1, 0);
	auto dist_to_focus = 10.0;
	auto aperture = 0.1;
	m_AspectRatio = 16.0 / 9.0;

	Camera cam(lookfrom, lookat, vup, 20, m_AspectRatio, aperture, dist_to_focus, 0.0, 1.0);

	m_Camera = cam;
}

// "next week" earth on perlin ground
void Scene::BuildScene6() {
	// world
	HittableList world;
	m_Background = Color(0.70, 0.80, 1.00);

	auto smoothPerText = make_shared<SmoothNoiseTexture>(4); // new perlin noise marble textures
	auto earthTexture = make_shared<ImageTexture>("res/textures/earthmap.jpg");

	world.Add(make_shared<Sphere>(Point3(0, -1000, 0), 1000, make_shared<Lambertian>(smoothPerText)));
	world.Add(make_shared<Sphere>(Point3(-1, 1, 2), 2, make_shared<Lambertian>(earthTexture)));

	m_World = world;

	// camera
	Point3 lookfrom(13, 2, 3);
	Point3 lookat(0, 0, 0);
	Vec3 vup(0, 1, 0);
	auto dist_to_focus = 10.0;
	auto aperture = 0.1;
	m_AspectRatio = 16.0 / 9.0;

	Camera cam(lookfrom, lookat, vup, 20, m_AspectRatio, aperture, dist_to_focus, 0.0, 1.0);

	m_Camera = cam;
}

// "next week" earth on perlin ground with sun
void Scene::BuildScene7() {
	// world
	HittableList world;
	m_Background = Color(0.0, 0.0, 0.0);

	auto smoothPerText = make_shared<SmoothNoiseTexture>(4); // new perlin noise marble textures
	auto earthTexture = make_shared<ImageTexture>("res/textures/earthmap.jpg");
	auto lightMaterial = make_shared<DiffuseLight>(Color(1.0, 1.0, 1.0));

	world.Add(make_shared<Sphere>(Point3(0, -1000, 0), 1000, make_shared<Lambertian>(smoothPerText)));
	world.Add(make_shared<Sphere>(Point3(1, 2.5, -2), 1, lightMaterial));
	world.Add(make_shared<Sphere>(Point3(-1, 1, 2), 2, make_shared<Lambertian>(earthTexture)));

	m_World = world;

	// camera
	Point3 lookfrom(13, 2, 3);
	Point3 lookat(0, 0, 0);
	Vec3 vup(0, 1, 0);
	auto dist_to_focus = 10.0;
	auto aperture = 0.1;
	m_AspectRatio = 16.0 / 9.0;

	Camera cam(lookfrom, lookat, vup, 20, m_AspectRatio, aperture, dist_to_focus, 0.0, 1.0);

	m_Camera = cam;
}

// "next week" earth on perlin ground with two light spheres and a light portal
void Scene::BuildScene8() {
	// world
	HittableList world;
	m_Background = Color(0.0, 0.0, 0.0);

	auto smoothPerText = make_shared<SmoothNoiseTexture>(4); // new perlin noise marble textures
	auto earthTexture = make_shared<ImageTexture>("res/textures/earthmap.jpg");
	auto lightMaterial = make_shared<DiffuseLight>(Color(1.0, 1.0, 1.0));

	world.Add(make_shared<Sphere>(Point3(0, -1000, 0), 1000, make_shared<Lambertian>(smoothPerText)));
	world.Add(make_shared<Sphere>(Point3(-1, 1, 0), 2, make_shared<Lambertian>(earthTexture)));
	world.Add(make_shared<Sphere>(Point3(-3, 2.5, 3), 1, lightMaterial));
	world.Add(make_shared<Sphere>(Point3(7, 6, 5), 3, lightMaterial));
	world.Add(make_shared<XYRect>(-3, 1, 0.5, 2.5, -3, lightMaterial));

	m_World = world;

	// camera
	Point3 lookfrom(26, 3, 6);
	Point3 lookat(0, 2, 0);
	Vec3 vup(0, 1, 0);
	auto dist_to_focus = 10.0;
	auto aperture = 0.1;
	m_AspectRatio = 16.0 / 9.0;

	Camera cam(lookfrom, lookat, vup, 20, m_AspectRatio, aperture, dist_to_focus, 0.0, 1.0);

	m_Camera = cam;
}

// "next week" Cornell box
void Scene::BuildScene9() {
	// world
	HittableList world;
	m_Background = Color(0.0, 0.0, 0.0);

	auto red   = make_shared<Lambertian>(Color(0.65, 0.05, 0.05));
	auto white = make_shared<Lambertian>(Color(0.73, 0.73, 0.73));
	auto green = make_shared<Lambertian>(Color(0.12, 0.45, 0.15));
	auto light = make_shared<DiffuseLight>(Color(15, 15, 15));

	world.Add(make_shared<YZRect>(0, 555, 0, 555, 555, green));
	world.Add(make_shared<YZRect>(0, 555, 0, 555, 0, red));
	world.Add(make_shared<XZRect>(127, 427, 127, 427, 554, light));
	world.Add(make_shared<XZRect>(0, 555, 0, 555, 0, white));
	world.Add(make_shared<XYRect>(0, 555, 0, 555, 555, white));
	world.Add(make_shared<XYRect>(0, 555, 0, 555, 555, white));

	m_World = world;

	// camera
	Point3 lookfrom(278, 278, -800);
	Point3 lookat(278, 278, 0);
	Vec3 vup(0, 1, 0);
	auto dist_to_focus = 10.0;
	auto aperture = 0.1;
	m_AspectRatio = 1.0;
	auto vfov = 40.0;

	Camera cam(lookfrom, lookat, vup, vfov, m_AspectRatio, aperture, dist_to_focus, 0.0, 1.0);

	m_Camera = cam;
}

// "next week" Cornell box with rectanglular boxes
void Scene::BuildScene10() {
	// world
	HittableList world;
	m_Background = Color(0.0, 0.0, 0.0);

	auto red = make_shared<Lambertian>(Color(0.65, 0.05, 0.05));
	auto white = make_shared<Lambertian>(Color(0.73, 0.73, 0.73));
	auto green = make_shared<Lambertian>(Color(0.12, 0.45, 0.15));
	auto light = make_shared<DiffuseLight>(Color(1.0, 1.0, 1.0));

	world.Add(make_shared<YZRect>(0, 555, 0, 555, 555, green));
	world.Add(make_shared<YZRect>(0, 555, 0, 555, 0, red));
	world.Add(make_shared<XZRect>(127, 427, 127, 427, 554, light));
	world.Add(make_shared<XZRect>(0, 555, 0, 555, 0, white));
	world.Add(make_shared<XYRect>(0, 555, 0, 555, 555, white));
	world.Add(make_shared<XYRect>(0, 555, 0, 555, 555, white));

	shared_ptr<Hittable> box1 = make_shared<Box>(Point3(0, 0, 0), Point3(165, 165, 165), white);
	box1 = make_shared<RotateY>(box1, -18);
	box1 = make_shared<Translate>(box1, Vec3(130, 0, 65));
	world.Add(box1);

	shared_ptr<Hittable> box2 = make_shared<Box>(Point3(0, 0, 0), Point3(165, 330, 165), white);
	box2 = make_shared<RotateY>(box2, 15);
	box2 = make_shared<Translate>(box2, Vec3(265, 0, 295));
	world.Add(box2);

	m_World = world;

	// camera
	Point3 lookfrom(278, 278, -800);
	Point3 lookat(278, 278, 0);
	Vec3 vup(0, 1, 0);
	auto dist_to_focus = 10.0;
	auto aperture = 0.1;
	m_AspectRatio = 1.0;
	auto vfov = 40.0;

	Camera cam(lookfrom, lookat, vup, vfov, m_AspectRatio, aperture, dist_to_focus, 0.0, 1.0);

	m_Camera = cam;
}

// "next week" Cornell box with rectanglular boxes and a cloud/smoke ball
void Scene::BuildScene11() {
	// world
	HittableList world;
	m_Background = Color(0.0, 0.0, 0.0);

	auto red = make_shared<Lambertian>(Color(0.65, 0.05, 0.05));
	auto white = make_shared<Lambertian>(Color(0.73, 0.73, 0.73));
	auto green = make_shared<Lambertian>(Color(0.12, 0.45, 0.15));
	auto light = make_shared<DiffuseLight>(Color(7, 7, 7));
	auto yellow = make_shared<Lambertian>(Color(0.98, 0.73, 0.02));

	world.Add(make_shared<YZRect>(0, 555, 0, 555, 555, green));
	world.Add(make_shared<YZRect>(0, 555, 0, 555, 0, red));
	world.Add(make_shared<XZRect>(127, 427, 127, 427, 554, light));
	world.Add(make_shared<XZRect>(0, 555, 0, 555, 0, white));
	world.Add(make_shared<XYRect>(0, 555, 0, 555, 555, white));
	world.Add(make_shared<XYRect>(0, 555, 0, 555, 555, white));

	shared_ptr<Hittable> box1 = make_shared<Box>(Point3(0, 0, 0), Point3(165, 165, 165), white);
	box1 = make_shared<RotateY>(box1, -18);
	box1 = make_shared<Translate>(box1, Vec3(130, 0, 65));
	world.Add(box1);

	shared_ptr<Hittable> box2 = make_shared<Box>(Point3(0, 0, 0), Point3(165, 330, 165), white);
	box2 = make_shared<RotateY>(box2, 15);
	box2 = make_shared<Translate>(box2, Vec3(265, 0, 295));
	world.Add(box2);

	world.Add(make_shared<ConstantMedium>(make_shared<Sphere>(Point3(270, 300, -200), 100, yellow), 0.01, Color(0.98, 0.73, 0.02)));

	m_World = world;

	// camera
	Point3 lookfrom(278, 278, -800);
	Point3 lookat(278, 278, 0);
	Vec3 vup(0, 1, 0);
	auto dist_to_focus = 10.0;
	auto aperture = 0.1;
	m_AspectRatio = 1.0;
	auto vfov = 40.0;

	Camera cam(lookfrom, lookat, vup, vfov, m_AspectRatio, aperture, dist_to_focus, 0.0, 1.0);

	m_Camera = cam;
}

// "next week" final scene with all features
void Scene::BuildScene12() {
	// world
	HittableList world;
	
	// wall of "bricks"
	HittableList wall;
	auto blue = make_shared<Lambertian>(Color(0.26, 0.52, 0.96));

	const int boxes_per_side = 20;
	for (int i = 0; i < boxes_per_side; i++) {
		for (int j = 0; j < boxes_per_side; j++) {
			auto w = 100.0;
			auto x0 = RandomDouble(600, 699);
			auto y0 = -1000.0 + i * w;
			auto z0 = -1000.0 + j * w;
			auto x1 = 700;
			auto y1 = y0 + w;
			auto z1 = z0 + w;

			wall.Add(make_shared<Box>(Point3(x0, y0, z0), Point3(x1, y1, z1), blue));
		}
	}
	// add wall to world
	world.Add(make_shared<BVHNode>(wall, 0, 1)); 

	// rectangular smoke over top of light ball
	auto white = make_shared<Lambertian>(Color(0.8, 0.8, 0.8));
	world.Add(make_shared<ConstantMedium>(make_shared<Box>(Point3(95, 200, -80), Point3(255, 250, 80), white), 0.01, Color(1, 1, 1))); 
	// light ball
	auto lightMat = make_shared<DiffuseLight>(Color(12, 12, 12));
	world.Add(make_shared<Sphere>(Point3(175, 200, 0), 75, lightMat)); 
	
	// spheres in a cube box
	HittableList spheres;
	auto penguinTexture = make_shared<ImageTexture>("res/textures/Penguin.png");

	int numSpheres = 1000;
	for (int j = 0; j < numSpheres; j++) {
		spheres.Add(make_shared<Sphere>(Point3(RandomDouble(-25, 75), RandomDouble(-50, 50), RandomDouble(200, 300)), 10, make_shared<Lambertian>(penguinTexture)));
	}
	// add spheres in cube to world
	world.Add(make_shared<RotateX>(make_shared<BVHNode>(spheres, 0.0, 1.0), 45));

	// add glass sphere
	world.Add(make_shared<Sphere>(Point3(350, -50, -250), 70, make_shared<Dielectric>(1.5)));

	// fuzzy metal box
	world.Add(make_shared<RotateZ>(make_shared<Box>(Point3(200, -100, 0), Point3(400, 100, 200), make_shared<Metal>(Color(1.0, 0.8, 0.8), 1.0)), 15));

	// shiny metal box
	world.Add(make_shared<Box>(Point3(50, -150, -150), Point3(150, -50, -100), make_shared<Metal>(Color(0.8, 0.8, 0.8), 0.0)));

	// subsurface material
	auto boundary = make_shared<RotateY>(make_shared<Box>(Point3(-90, -90, -40), Point3(-10, -10, 40), make_shared<Dielectric>(1.5)), 40);
	world.Add(boundary);
	world.Add(make_shared<ConstantMedium>(boundary, 0.2, Color(0.98, 0.76, 0.09)));

	// light ball from behind camera to light up scene
	auto backLight = make_shared<DiffuseLight>(Color(15, 15, 15));
	world.Add(make_shared<Sphere>(Point3(-300, 150, -700), 100, backLight));
	// light ball from bottom right to light up scene
	world.Add(make_shared<Sphere>(Point3(-500, -400, -70), 100, backLight));

	m_World = world;

	// camera
	Point3 lookfrom(-200, 50, -600);
	Point3 lookat(300, 0, 100);
	Vec3 vup(0, 1, 0);
	auto dist_to_focus = 10.0;
	auto aperture = 0.1;
	m_AspectRatio = 16.0/9.0;
	auto vfov = 40.0;
	m_Background = Color(0.1, 0.1, 0.1);

	Camera cam(lookfrom, lookat, vup, vfov, m_AspectRatio, aperture, dist_to_focus, 0.0, 1.0);

	m_Camera = cam;
}