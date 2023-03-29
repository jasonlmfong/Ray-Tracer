#include "HittableList.h"

HittableList::HittableList()
{
}

HittableList::HittableList(shared_ptr<Hittable> object)
{
	Add(object);
}

void HittableList::Clear()
{
	objects.clear();
}

void HittableList::Add(shared_ptr<Hittable> object)
{
	objects.push_back(object);
}

bool HittableList::Hit(const Ray& r, double t_min, double t_max, hitRecord& rec) const
{
    hitRecord temp_rec;
    bool hit_anything = false;
    auto closest_so_far = t_max;

    for (const auto& object : objects) {
        if (object->Hit(r, t_min, closest_so_far, temp_rec)) {
            hit_anything = true;
            closest_so_far = temp_rec.t;
            rec = temp_rec;
        }
    }

    return hit_anything;
}
