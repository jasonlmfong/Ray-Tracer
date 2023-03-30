#include "BVH.h"

BVHNode::BVHNode()
{
}

BVHNode::BVHNode(const HittableList& list, double time0, double time1)
    : BVHNode(list.objects, 0, list.objects.size(), time0, time1)
{
}

BVHNode::BVHNode(const std::vector<shared_ptr<Hittable>>& src_objects, size_t start, size_t end, double time0, double time1)
{
    auto objects = src_objects; // Create a modifiable array of the source scene objects

    int axis = RandomInt(0, 2);
    auto comparator = (axis == 0) ? BoxXCompare : (axis == 1) ? BoxYCompare : BoxZCompare;

    size_t object_span = end - start;

    if (object_span == 1) {
        left = right = objects[start];
    }
    else if (object_span == 2) {
        if (comparator(objects[start], objects[start + 1])) {
            left = objects[start];
            right = objects[start + 1];
        }
        else {
            left = objects[start + 1];
            right = objects[start];
        }
    }
    else {
        std::sort(objects.begin() + start, objects.begin() + end, comparator);

        auto mid = start + object_span / 2;
        left = make_shared<BVHNode>(objects, start, mid, time0, time1);
        right = make_shared<BVHNode>(objects, mid, end, time0, time1);
    }

    AABB box_left, box_right;

    if (!left->BoundingBox(time0, time1, box_left)
        || !right->BoundingBox(time0, time1, box_right)
        )
        std::cerr << "No bounding box in bvh_node constructor.\n";

    box = SurroundingBox(box_left, box_right);
}

bool BVHNode::Hit(const Ray& r, double t_min, double t_max, hitRecord& rec) const
{
    if (!box.Hit(r, t_min, t_max))
        return false;

    bool hit_left = left->Hit(r, t_min, t_max, rec);
    bool hit_right = right->Hit(r, t_min, hit_left ? rec.t : t_max, rec);

    return hit_left || hit_right;
}

bool BVHNode::BoundingBox(double time0, double time1, AABB& output_box) const 
{
    output_box = box;
    return true;
}
