#pragma once
#ifndef HITTABLE_H
#define HITTABLE_H

#include "../../utils/Utils.h"
#include "../../utils/Ray.h"

//#include "../AABB.h"

class Material;

struct hitRecord
{
    Point3 p;
    Vec3 normal;
    Material* mat_ptr;
    float t;
    float u;
    float v;

    bool front_face;

    __device__ inline void SetFaceNormal(const Ray& r, const Vec3& outward_normal) {
        front_face = Dot(r.GetDirection(), outward_normal) < 0;
        normal = front_face ? outward_normal : -outward_normal;
    }
};

class Hittable  
{
    public:
        __device__ virtual bool Hit(const Ray& r, float t_min, float t_max, hitRecord& rec) const = 0;
        //__device__ virtual bool BoundingBox(float time0, float time1, AABB& output_box) const = 0;
};

#endif
