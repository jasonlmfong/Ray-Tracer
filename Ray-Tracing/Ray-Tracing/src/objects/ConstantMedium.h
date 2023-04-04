#pragma once
#ifndef CONSTANTMEDIUM_H
#define CONSTANTMEDIUM_H

#include "../Utils.h"

#include "Hittable.h"
#include "Material.h"
#include "Texture.h"

class ConstantMedium : public Hittable {
public:
    ConstantMedium(shared_ptr<Hittable> b, double density, shared_ptr<Texture> a);

    ConstantMedium(shared_ptr<Hittable> b, double density, Color c);

    virtual bool Hit(const Ray& r, double t_min, double t_max, hitRecord& rec) const override;

    virtual bool BoundingBox(double time0, double time1, AABB& output_box) const override;

public:
    shared_ptr<Hittable> m_Boundary;
    shared_ptr<Material> m_PhaseFunction;
    double m_NegativeInvDensity;
};

#endif