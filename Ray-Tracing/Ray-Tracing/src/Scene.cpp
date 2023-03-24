#include "Scene.h"
#include "Material.h"
#include "Sphere.h"

Scene::Scene()
	:
	m_Camera(vec3(0.0, 0.0, 0.0),
		vec3(0.0, 0.0, -1.0),
		vec3(0.0, 1.0, 0.0),
		60.0,
		16.0 / 9.0,
		0.1,
		(vec3(0.0, 0.0, 0.0) - vec3(0.0, 0.0, -1.0)).length()
	)
{}

void Scene::BuildScene1() {
	// world
	hittable_list world;

	auto material_ground = make_shared<lambertian>(color(0.8, 0.8, 0.0));
	auto material_center = make_shared<lambertian>(color(0.7, 0.3, 0.3));
	auto material_left = make_shared<dielectric>(1.5);
	auto material_right = make_shared<metal>(color(0.8, 0.6, 0.2), 1.0);

	world.add(make_shared<sphere>(point3(0.0, -100.5, -1.0), 100.0, material_ground));
	world.add(make_shared<sphere>(point3(0.0, 0.0, -1.5), 0.5, material_center));
	world.add(make_shared<sphere>(point3(-1.0, 0.0, -2.0), -0.4, material_left));
	world.add(make_shared<sphere>(point3(1.0, 0.0, -1.0), 0.5, material_right));

	m_World = world;

	// camera
	point3 lookfrom(3, 3, 2);
	point3 lookat(0, 0, -1);
	vec3 vup(0, 1, 0);
	auto dist_to_focus = (lookfrom - lookat).length();
	auto aperture = 2.0;
	auto aspect_ratio = 16.0 / 9.0;

	camera cam(lookfrom, lookat, vup, 20, aspect_ratio, aperture, dist_to_focus);

	m_Camera = cam;
}

//void Scene::BuildScene2() {
//	hittable_list objects;
//
//	std::shared_ptr<Material> red = std::make_shared<Lambertian>(vec3(0.65, 0.05, 0.05));
//	std::shared_ptr<Material> white = std::make_shared<Lambertian>(vec3(0.73, 0.73, 0.73));
//	std::shared_ptr<Material> green = std::make_shared<Lambertian>(vec3(0.12, 0.45, 0.15));
//	std::shared_ptr<Material> light = std::make_shared<DiffuseLight>(vec3(15.0, 15.0, 15.0));
//
//	objects.add(std::make_shared<YZRect>(0.0, 555.0, 0.0, 555.0, 555.0, green));
//	objects.add(std::make_shared<YZRect>(0.0, 555.0, 0.0, 555.0, 0.0, red));
//	objects.add(std::make_shared<XZRect>(213.0, 343.0, 227.0, 332.0, 554.0, light));
//	objects.add(std::make_shared<XZRect>(0.0, 555.0, 0.0, 555.0, 0.0, white));
//	objects.add(std::make_shared<XZRect>(0.0, 555.0, 0.0, 555.0, 555.0, white));
//	objects.add(std::make_shared<XYRect>(0.0, 555.0, 0.0, 555.0, 555.0, white));
//
//	std::shared_ptr<HittableObject> box1 = std::make_shared<Box>(vec3(0.0, 0.0, 0.0), vec3(165.0, 330.0, 165.0), white);
//	box1 = std::make_shared<RotateY>(box1, 15.0);
//	box1 = std::make_shared<Translate>(box1, vec3(265.0, 0.0, 295.0));
//
//	std::shared_ptr<HittableObject> box2 = std::make_shared<Box>(vec3(0.0, 0.0, 0.0), vec3(165.0, 165.0, 165.0), white);
//	box2 = std::make_shared<RotateY>(box2, -18.0);
//	box2 = std::make_shared<Translate>(box2, vec3(130.0, 0.0, 65.0));
//
//	objects.add(box1);
//	objects.add(box2);
//
//	m_HittableObjectList = objects;
//
//	vec3 cameraPosition(278.0, 278.0, -800.0);
//	vec3 lookAt(278.0, 278.0, 0.0);
//	vec3 up(0.0, 1.0, 0.0);
//	double focusDistance = glm::length(cameraPosition - lookAt);
//	double aperture = 0.0;
//	double vFOV = 40.0;
//	double imageAspectRatio = 1.0;
//
//	Camera camera(cameraPosition, lookAt, up, vFOV, imageAspectRatio, aperture, focusDistance, 0.0, 1.0);
//
//	m_Camera = camera;
//}