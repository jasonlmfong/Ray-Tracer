#include "Scene.h"

Scene::Scene()
    :m_Camera(Vec3(0.0f, 0.0f, 0.0f),
        Vec3(0.0f, 0.0f, -1.0f),
        Vec3(0.0, 1.0, 0.0),
        60.0,
        16.0 / 9.0,
        0.1,
        (Vec3(0.0, 0.0, 0.0) - Vec3(0.0, 0.0, -1.0)).length()
    )
{}

void Scene::BuildScene2() {
	// world
	HittableList world;

	auto ground_material = make_shared<Lambertian>(Vec3(0.5, 0.5, 0.5));
	world.add(make_shared<Sphere>(Vec3(0, -1000, 0), 1000, ground_material));

	for (int a = -11; a < 11; a++) {
		for (int b = -11; b < 11; b++) {
			auto choose_mat = randomDouble();
			Vec3 center(a + 0.9 * randomDouble(), 0.2, b + 0.9 * randomDouble());

			if ((center - Vec3(4, 0.2, 0)).length() > 0.9) {
				shared_ptr<Material> Sphere_material;

				if (choose_mat < 0.8) {
					// diffuse
					auto albedo = randomVec3() * randomVec3();
					Sphere_material = make_shared<Lambertian>(albedo);
					world.add(make_shared<Sphere>(center, 0.2, Sphere_material));
				}
				else if (choose_mat < 0.95) {
					// metal
					auto albedo = randomVec3(0.5, 1);
					auto fuzz = randomDouble(0, 0.5);
					Sphere_material = make_shared<Metal>(albedo, fuzz);
					world.add(make_shared<Sphere>(center, 0.2, Sphere_material));
				}
				else {
					// glass
					Sphere_material = make_shared<Dielectric>(1.5);
					world.add(make_shared<Sphere>(center, 0.2, Sphere_material));
				}
			}
		}
	}

	auto material1 = make_shared<Dielectric>(1.5);
	world.add(make_shared<Sphere>(Vec3(0, 1, 0), 1.0, material1));

	auto material2 = make_shared<Lambertian>(Vec3(0.4, 0.2, 0.1));
	world.add(make_shared<Sphere>(Vec3(-4, 1, 0), 1.0, material2));

	auto material3 = make_shared<Metal>(Vec3(0.7, 0.6, 0.5), 0.0);
	world.add(make_shared<Sphere>(Vec3(4, 1, 0), 1.0, material3));

	m_World = world;

	// camera
	Vec3 lookfrom(13, 2, 3);
	Vec3 lookat(0, 0, 0);
	Vec3 vup(0, 1, 0);
	auto dist_to_focus = 10.0;
	auto aperture = 0.1;
	auto aspect_ratio = 16.0 / 9.0;

	Camera cam(lookfrom, lookat, vup, 20, aspect_ratio, aperture, dist_to_focus);

	m_Camera = cam;
}