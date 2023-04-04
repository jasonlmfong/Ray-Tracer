#pragma once

#include "Camera.h"
#include "objects/HittableList.h"
#include "objects/Material.h"
#include "objects/Sphere.h"
#include "objects/MovingSphere.h"
#include "objects/AARect.h"

class Scene {
public:
	Scene();

	void BuildScene1();
	void BuildScene2();
	void BuildScene3();
	void BuildScene4();
	void BuildScene5();
	void BuildScene6();
	void BuildScene7();
	void BuildScene8();
	void BuildScene9();

public:
	HittableList m_World;
	Camera m_Camera;
	Color m_Background;
	double m_AspectRatio;
};