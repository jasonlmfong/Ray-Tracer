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
	auto aspect_ratio = 16.0 / 9.0;

	Camera cam(lookfrom, lookat, vup, 45, aspect_ratio, aperture, dist_to_focus, 0, 0);

	m_Camera = cam;
}

// cover scene of "one weekend"
void Scene::BuildScene2() {
	// world
	HittableList world;

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
	auto aspect_ratio = 16.0 / 9.0;

	Camera cam(lookfrom, lookat, vup, 20, aspect_ratio, aperture, dist_to_focus, 0, 0);

	m_Camera = cam;
}

// "next week" bouncing balls with checkered ground
void Scene::BuildScene3() {
	// world
	HittableList world;

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
	auto aspect_ratio = 16.0 / 9.0;

	Camera cam(lookfrom, lookat, vup, 20, aspect_ratio, aperture, dist_to_focus, 0.0, 1.0);

	m_Camera = cam;
}

// "next week" two checkered spheres scene
void Scene::BuildScene4() {
	// world
	HittableList world;

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
	auto aspect_ratio = 16.0 / 9.0;

	Camera cam(lookfrom, lookat, vup, 20, aspect_ratio, aperture, dist_to_focus, 0.0, 1.0);

	m_Camera = cam;
}