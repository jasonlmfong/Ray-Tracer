#pragma once
#ifndef SCENE_H
#define SCENE_H

#include "Camera.h"

#include "Material.h"

#include "HittableList.h"
#include "Sphere.h"
#include "Vec3.h"

class Scene
{
public:
	Scene();

	__device__ void BuildScene1();

public:
	HittableList m_World;
	Camera m_Camera;
	float m_AspectRatio;
}

#endif