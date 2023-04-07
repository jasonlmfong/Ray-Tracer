#pragma once
#ifndef TRANSLATE_H
#define TRANSLATE_H

#include "objects/Hittable.h"

class Translate : public Hittable {
public:
    Translate(shared_ptr<Hittable> p, const Vec3& displacement);

    virtual bool Hit(const Ray& r, double t_min, double t_max, hitRecord& rec) const override;

    virtual bool BoundingBox(double time0, double time1, AABB& output_box) const override;

public:
    shared_ptr<Hittable> ptr;
    Vec3 offset;
};

#endif