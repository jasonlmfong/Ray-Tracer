#pragma once
#ifndef MOVING_SPHERE_H
#define MOVING_SPHERE_H

#include "../../utils/Utils.h"
#include "Hittable.h"

class MovingSphere : public Hittable {
public:
    __device__ MovingSphere();
    __device__ MovingSphere(Point3 cen0, Point3 cen1, float _time0, float _time1, float r, Material* m);

    __device__ virtual bool Hit(const Ray& r, float t_min, float t_max, hitRecord& rec) const override;
    //__device__ virtual bool BoundingBox(float _time0, float _time1, AABB& output_box) const override;

    __device__ Point3 GetCenter(float time) const;

public:
    Point3 center0, center1;
    float time0, time1;
    float radius;
    Material* mat_ptr;
};

#endif