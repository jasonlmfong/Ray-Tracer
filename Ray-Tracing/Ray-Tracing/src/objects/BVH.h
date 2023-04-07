#pragma once
#ifndef BVH_H
#define BVH_H

#include "../utils/Utils.h"

#include "objects/Hittable.h"
#include "objects/HittableList.h"

#include <algorithm>

class BVHNode : public Hittable {
public:
    BVHNode();
    BVHNode(const HittableList& list, double time0, double time1);

    BVHNode(const std::vector<shared_ptr<Hittable>>& src_objects, size_t start, size_t end, double time0, double time1);

    virtual bool Hit(const Ray& r, double t_min, double t_max, hitRecord& rec) const override;

    virtual bool BoundingBox(double time0, double time1, AABB& output_box) const override;

public:
    shared_ptr<Hittable> left;
    shared_ptr<Hittable> right;
    AABB box;
};

inline bool BoxCompare(const shared_ptr<Hittable> a, const shared_ptr<Hittable> b, int axis) {
    AABB box_a;
    AABB box_b;

    if (!a->BoundingBox(0, 0, box_a) || !b->BoundingBox(0, 0, box_b))
        std::cerr << "No bounding box in bvh_node constructor.\n";

    return box_a.Min().e[axis] < box_b.Min().e[axis];
}

inline bool BoxXCompare(const shared_ptr<Hittable> a, const shared_ptr<Hittable> b) {
    return BoxCompare(a, b, 0);
}

inline bool BoxYCompare(const shared_ptr<Hittable> a, const shared_ptr<Hittable> b) {
    return BoxCompare(a, b, 1);
}

inline bool BoxZCompare(const shared_ptr<Hittable> a, const shared_ptr<Hittable> b) {
    return BoxCompare(a, b, 2);
}

#endif