#pragma once

#include "HittableList.h"
#include "Camera.h"

class Scene {
public:
	Scene();
	void BuildScene1();
	void BuildScene2();

	HittableList m_World;
	Camera m_Camera;
};