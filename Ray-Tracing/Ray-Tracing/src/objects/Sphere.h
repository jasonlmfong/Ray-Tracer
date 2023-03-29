#pragma once
#ifndef SPHERE_H
#define SPHERE_H

#include "../Vec3.h"
#include "Hittable.h"

class Sphere : public Hittable {
public:
    Sphere();
    Sphere(Point3 cen, double r, shared_ptr<Material> m);

    bool Hit(const Ray& r, double t_min, double t_max, hitRecord& rec) const;

public:
    Point3 center;
    double radius;
    shared_ptr<Material> mat_ptr;
};

#endif