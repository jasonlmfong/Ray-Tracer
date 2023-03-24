#pragma once

#include "hittable_list.h"
#include "camera.h"

class Scene {
public:
	Scene();
	void BuildScene1();
	//void BuildScene2();

	hittable_list m_World;
	camera m_Camera;
};