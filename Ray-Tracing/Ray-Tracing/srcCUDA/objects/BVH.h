#pragma once
#ifndef BVH_H
#define BVH_H

#include "../utils/Utils.h"

#include "objects/Hittable.h"
#include "objects/HittableList.h"

#include <thrust/device_vector.h>
#include <algorithm>

class BVHNode : public Hittable {
public:
    __device__ BVHNode();
    __device__ BVHNode(const HittableList& hitList, float time0, float time1, curandState* local_rand_state);
    __device__ BVHNode(const thrust::device_vector<Hittable*>& src_objects, size_t start, size_t end, float time0, float time1, curandState* local_rand_state);

    __device__ virtual bool Hit(const Ray& r, float t_min, float t_max, hitRecord& rec) const override;
    __device__ virtual bool BoundingBox(float time0, float time1, AABB& output_box) const override;

public:
    Hittable* left;
    Hittable* right;
    AABB box;
};

__device__ inline bool BoxCompare(const Hittable* a, const Hittable* b, int axis) {
    AABB box_a;
    AABB box_b;

    if (!a->BoundingBox(0, 0, box_a) || !b->BoundingBox(0, 0, box_b))
        printf("No bounding box in bvh_node constructor.\n");

    return box_a.Min().e[axis] < box_b.Min().e[axis];
}

__device__ inline bool BoxXCompare(const Hittable* a, const Hittable* b) {
    return BoxCompare(a, b, 0);
}

__device__ inline bool BoxYCompare(const Hittable* a, const Hittable* b) {
    return BoxCompare(a, b, 1);
}

__device__ inline bool BoxZCompare(const Hittable* a, const Hittable* b) {
    return BoxCompare(a, b, 2);
}

#endif