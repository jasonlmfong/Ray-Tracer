#pragma once
#ifndef ROTATE_H
#define ROTATE_H

#include "objects/Hittable.h"

class RotateX : public Hittable {
public:
    RotateX(shared_ptr<Hittable> p, double angle);

    virtual bool Hit(const Ray& r, double t_min, double t_max, hitRecord& rec) const override;

    virtual bool BoundingBox(double time0, double time1, AABB& output_box) const override;

public:
    shared_ptr<Hittable> m_Ptr;
    double m_SinTheta;
    double m_CosTheta;
    bool m_HasBox;
    AABB m_BoundBox;
};

class RotateY : public Hittable {
public:
    RotateY(shared_ptr<Hittable> p, double angle);

    virtual bool Hit(const Ray& r, double t_min, double t_max, hitRecord& rec) const override;

    virtual bool BoundingBox(double time0, double time1, AABB& output_box) const override;

public:
    shared_ptr<Hittable> m_Ptr;
    double m_SinTheta;
    double m_CosTheta;
    bool m_HasBox;
    AABB m_BoundBox;
};

class RotateZ : public Hittable {
public:
    RotateZ(shared_ptr<Hittable> p, double angle);

    virtual bool Hit(const Ray& r, double t_min, double t_max, hitRecord& rec) const override;

    virtual bool BoundingBox(double time0, double time1, AABB& output_box) const override;

public:
    shared_ptr<Hittable> m_Ptr;
    double m_SinTheta;
    double m_CosTheta;
    bool m_HasBox;
    AABB m_BoundBox;
};

#endif