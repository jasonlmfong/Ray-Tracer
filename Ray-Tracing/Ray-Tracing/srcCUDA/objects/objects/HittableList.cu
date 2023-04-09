#include "HittableList.h"

__device__ HittableList::HittableList()
{
}

__device__ HittableList::HittableList(Hittable** l, int n)
{
    list = l; 
    list_size = n; 
}

__device__ bool HittableList::Hit(const Ray& r, float tmin, float tmax, hitRecord& rec) const
{
    hitRecord temp_rec;
    bool hit_anything = false;
    float closest_so_far = tmax;
    for (int i = 0; i < list_size; i++) {
        if (list[i]->Hit(r, tmin, closest_so_far, temp_rec)) {
            hit_anything = true;
            closest_so_far = temp_rec.t;
            rec = temp_rec;
        }
    }
    return hit_anything;
}

//__device__ bool HittableList::BoundingBox(float time0, float time1, AABB& output_box) const
//{
//    if (list_size == 0) 
//        return false;
//
//    AABB temp_box;
//    bool first_box = true;
//
//    for (int i = 0; i < list_size; i++) {
//        if (!list[i]->BoundingBox(time0, time1, temp_box)) return false;
//        output_box = first_box ? temp_box : SurroundingBox(output_box, temp_box);
//        first_box = false;
//    }
//
//    return true;
//}
