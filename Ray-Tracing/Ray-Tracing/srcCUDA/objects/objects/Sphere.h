#pragma once
#ifndef SPHERE_H
#define SPHERE_H

#include "Hittable.h"

class Sphere: public Hittable 
{
public:
    __device__ Sphere();
    __device__ Sphere(Point3 cen, float r, Material* m);

    __device__ virtual bool Hit(const Ray& r, float tmin, float tmax, hitRecord& rec) const override;
    //__device__ virtual bool BoundingBox(float time0, float time1, AABB& output_box) const override;

public:
    Vec3 center;
    float radius;
    Material *mat_ptr;

private:
    __device__ static void GetSphereUV(const Point3& p, float& u, float& v);
};

#endif
