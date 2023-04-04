#include "ConstantMedium.h"

ConstantMedium::ConstantMedium(shared_ptr<Hittable> b, double density, shared_ptr<Texture> a)
    : m_Boundary(b), m_NegativeInvDensity(-1 / density), m_PhaseFunction(make_shared<Isotropic>(a))
{
}

ConstantMedium::ConstantMedium(shared_ptr<Hittable> b, double density, Color c)
    : m_Boundary(b), m_NegativeInvDensity(-1 / density), m_PhaseFunction(make_shared<Isotropic>(c))
{
}

bool ConstantMedium::Hit(const Ray& r, double t_min, double t_max, hitRecord& rec) const
{
    hitRecord rec1, rec2;

    if (!m_Boundary->Hit(r, -infinity, infinity, rec1))
        return false;

    if (!m_Boundary->Hit(r, rec1.t + 0.0001, infinity, rec2))
        return false;

    if (rec1.t < t_min) rec1.t = t_min;
    if (rec2.t > t_max) rec2.t = t_max;

    if (rec1.t >= rec2.t)
        return false;

    if (rec1.t < 0)
        rec1.t = 0;

    const auto ray_length = r.GetDirection().Length();
    const auto distance_inside_boundary = (rec2.t - rec1.t) * ray_length;
    const auto hit_distance = m_NegativeInvDensity * log(RandomDouble());

    if (hit_distance > distance_inside_boundary)
        return false;

    rec.t = rec1.t + hit_distance / ray_length;
    rec.p = r.GetPosAtDir(rec.t);

    rec.normal = Vec3(1, 0, 0);  // arbitrary
    rec.front_face = true;     // also arbitrary
    rec.mat_ptr = m_PhaseFunction;

    return true;
}

bool ConstantMedium::BoundingBox(double time0, double time1, AABB& output_box) const
{
    return m_Boundary->BoundingBox(time0, time1, output_box);
}
