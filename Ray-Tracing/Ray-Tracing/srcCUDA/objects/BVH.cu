#include "BVH.h"

__device__ BVHNode::BVHNode()
{
}

__device__ BVHNode::BVHNode(const HittableList& hitList, float time0, float time1, curandState* local_rand_state)
    : BVHNode(hitList.list, 0, hitList.list_size * sizeof(Hittable), time0, time1, local_rand_state)
{
}

__device__ BVHNode::BVHNode(const thrust::device_vector<Hittable*>& src_objects, size_t start, size_t end, float time0, float time1, curandState* local_rand_state)
{
    auto objects = src_objects; // Create a modifiable array of the source scene objects

    int axis = RandomInt(0, 2, local_rand_state);
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
        left = &BVHNode(objects, start, mid, time0, time1, local_rand_state);
        right = &BVHNode(objects, mid, end, time0, time1, local_rand_state);
    }

    AABB box_left, box_right;

    if (!left->BoundingBox(time0, time1, box_left)
        || !right->BoundingBox(time0, time1, box_right)
        )
        printf("No bounding box in bvh_node constructor.\n");

    box = SurroundingBox(box_left, box_right);
}

__device__ bool BVHNode::Hit(const Ray& r, float t_min, float t_max, hitRecord& rec) const
{
    if (!box.Hit(r, t_min, t_max))
        return false;

    bool hit_left = left->Hit(r, t_min, t_max, rec);
    bool hit_right = right->Hit(r, t_min, hit_left ? rec.t : t_max, rec);

    return hit_left || hit_right;
}

__device__ bool BVHNode::BoundingBox(float time0, float time1, AABB& output_box) const
{
    output_box = box;
    return true;
}
