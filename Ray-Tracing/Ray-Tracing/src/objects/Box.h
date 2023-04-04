#pragma once
#ifndef Box_H
#define Box_H

#include "../Utils.h"

#include "AARect.h"
#include "HittableList.h"

class Box : public Hittable {
public:
    Box();
    Box(const Point3& p0, const Point3& p1, shared_ptr<Material> ptr);

    virtual bool Hit(const Ray& r, double t_min, double t_max, hitRecord& rec) const override;

    virtual bool BoundingBox(double time0, double time1, AABB& output_Box) const override;

public:
    Point3 m_BoxMin;
    Point3 m_BoxMax;
    HittableList m_Sides;
};

#endif