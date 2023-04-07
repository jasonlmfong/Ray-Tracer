#pragma once

#include "Camera.h"

#include "objects/materials/Material.h"
#include "objects/materials/ConstantMedium.h"

#include "objects/objects/HittableList.h"
#include "objects/objects/Sphere.h"
#include "objects/objects/MovingSphere.h"
#include "objects/objects/AARect.h"
#include "objects/objects/Box.h"

#include "objects/Translate.h"
#include "objects/Rotate.h"
#include "objects/BVH.h"

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
	void BuildScene10();
	void BuildScene11();
	void BuildScene12();

public:
	HittableList m_World;
	Camera m_Camera;
	Color m_Background;
	double m_AspectRatio;
};