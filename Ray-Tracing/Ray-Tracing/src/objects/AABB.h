#pragma once
#ifndef AABB_H
#define AABB_H

#include "../utils/Utils.h"

class AABB {
public:
    AABB();
    AABB(const Point3& a, const Point3& b);

    Point3 Min() const;
    Point3 Max() const;

    bool Hit(const Ray& r, double t_min, double t_max) const;

    Point3 minimum;
    Point3 maximum;
};

inline AABB SurroundingBox(AABB box0, AABB box1)
{
    Point3 small(fmin(box0.Min().x(), box1.Min().x()),
        fmin(box0.Min().y(), box1.Min().y()),
        fmin(box0.Min().z(), box1.Min().z()));

    Point3 big(fmax(box0.Max().x(), box1.Max().x()),
        fmax(box0.Max().y(), box1.Max().y()),
        fmax(box0.Max().z(), box1.Max().z()));

    return AABB(small, big);
}

#endif