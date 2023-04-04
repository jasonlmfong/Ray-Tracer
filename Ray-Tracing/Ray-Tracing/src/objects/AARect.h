#pragma once
#ifndef AARECT_H
#define AARECT_H

#include "../Utils.h"

#include "Hittable.h"

class XYRect : public Hittable {
public:
    XYRect();

    XYRect(double _x0, double _x1, double _y0, double _y1, double _z, shared_ptr<Material> mat);

    virtual bool Hit(const Ray& r, double t_min, double t_max, hitRecord& rec) const override;

    virtual bool BoundingBox(double time0, double time1, AABB& output_box) const override;

public:
    shared_ptr<Material> matPtr;
    double x0, x1, y0, y1, z;
};

class XZRect : public Hittable {
public:
    XZRect();

    XZRect(double _x0, double _x1, double _z0, double _z1, double _y, shared_ptr<Material> mat);

    virtual bool Hit(const Ray& r, double t_min, double t_max, hitRecord& rec) const override;

    virtual bool BoundingBox(double time0, double time1, AABB& output_box) const override;

public:
    shared_ptr<Material> matPtr;
    double x0, x1, z0, z1, y;
};

class YZRect : public Hittable {
public:
    YZRect();

    YZRect(double _y0, double _y1, double _z0, double _z1, double _x, shared_ptr<Material> mat);

    virtual bool Hit(const Ray& r, double t_min, double t_max, hitRecord& rec) const override;

    virtual bool BoundingBox(double time0, double time1, AABB& output_box) const override;

public:
    shared_ptr<Material> matPtr;
    double y0, y1, z0, z1, x;
};

#endif