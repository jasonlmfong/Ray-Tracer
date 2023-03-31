#pragma once
#ifndef HITTABLE_H
#define HITTABLE_H

#include "../Ray.h"
#include "../Utils.h"

#include "AABB.h"

class Material;

struct hitRecord {
    Point3 p;
    Vec3 normal;
    shared_ptr<Material> mat_ptr;
    double t;
    double u;
    double v;
    bool front_face;

    inline void SetFaceNormal(const Ray& r, const Vec3& outward_normal) {
        front_face = Dot(r.GetDirection(), outward_normal) < 0;
        normal = front_face ? outward_normal : -outward_normal;
    }
};

class Hittable {
public:
    virtual bool Hit(const Ray& r, double t_min, double t_max, hitRecord& rec) const = 0;
    virtual bool BoundingBox(double time0, double time1, AABB& output_box) const = 0;
};

#endif