#include "Translate.h"

Translate::Translate(shared_ptr<Hittable> p, const Vec3& displacement)
    : ptr(p), offset(displacement) 
{
}

bool Translate::Hit(const Ray& r, double t_min, double t_max, hitRecord& rec) const
{
    Ray moved_r(r.GetOrigin() - offset, r.GetDirection(), r.GetTime());
    if (!ptr->Hit(moved_r, t_min, t_max, rec))
        return false;

    rec.p += offset;
    rec.SetFaceNormal(moved_r, rec.normal);

    return true;
}

bool Translate::BoundingBox(double time0, double time1, AABB& output_box) const
{
    if (!ptr->BoundingBox(time0, time1, output_box))
        return false;

    output_box = AABB(
        output_box.Min() + offset,
        output_box.Max() + offset);

    return true;
}
