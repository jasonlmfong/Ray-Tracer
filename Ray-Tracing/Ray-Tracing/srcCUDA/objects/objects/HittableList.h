#pragma once
#ifndef HITTABLE_LIST_H
#define HITTABLE_LIST_H

#include "Hittable.h"

class HittableList: public Hittable  
{
public:
    __device__ HittableList();
    __device__ HittableList(Hittable** l, int n);

    __device__ virtual bool Hit(const Ray& r, float tmin, float tmax, hitRecord& rec) const override;
    //__device__ virtual bool BoundingBox(float time0, float time1, AABB& output_box) const override;

public:
    Hittable** list;
    int list_size;
};

#endif
