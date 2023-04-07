#pragma once
#ifndef SPHERE_H
#define SPHERE_H

#include "../utils/Vec3.h"
#include "Hittable.h"

class Sphere : public Hittable {
public:
    Sphere();
    Sphere(Point3 cen, double r, shared_ptr<Material> m);

    virtual bool Hit(const Ray& r, double t_min, double t_max, hitRecord& rec) const override;
    virtual bool BoundingBox(double time0, double time1, AABB& output_box) const override;

public:
    Point3 center;
    double radius;
    shared_ptr<Material> mat_ptr;

private:
    static void GetSphereUV(const Point3& p, double& u, double& v);
};

#endif