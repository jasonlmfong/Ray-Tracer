#pragma once
#ifndef MOVING_SPHERE_H
#define MOVING_SPHERE_H

#include "Utils.h"
#include "Hittable.h"

class MovingSphere : public Hittable {
public:
    MovingSphere();
    MovingSphere(Point3 cen0, Point3 cen1, double _time0, double _time1, double r, shared_ptr<Material> m);

    virtual bool hit(const Ray& r, double t_min, double t_max, hitRecord& rec) const override;

    Point3 center(double time) const;

public:
    Point3 center0, center1;
    double time0, time1;
    double radius;
    shared_ptr<Material> mat_ptr;
};

#endif