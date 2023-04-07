#include "MovingSphere.h"

MovingSphere::MovingSphere()
{
}

MovingSphere::MovingSphere(Point3 cen0, Point3 cen1, double _time0, double _time1, double r, shared_ptr<Material> m)
	: center0(cen0), center1(cen1), time0(_time0), time1(_time1), radius(r), mat_ptr(m)
{
}

bool MovingSphere::Hit(const Ray& r, double t_min, double t_max, hitRecord& rec) const 
{
    Vec3 oc = r.GetOrigin() - GetCenter(r.GetTime());
    auto a = r.GetDirection().LengthSquared();
    auto half_b = Dot(oc, r.GetDirection());
    auto c = oc.LengthSquared() - radius * radius;

    auto discriminant = half_b * half_b - a * c;
    if (discriminant < 0) return false;
    auto sqrtd = sqrt(discriminant);

    // Find the nearest root that lies in the acceptable range.
    auto root = (-half_b - sqrtd) / a;
    if (root < t_min || t_max < root) {
        root = (-half_b + sqrtd) / a;
        if (root < t_min || t_max < root)
            return false;
    }

    rec.t = root;
    rec.p = r.GetPosAtDir(rec.t);
    auto outward_normal = (rec.p - GetCenter(r.GetTime())) / radius;
    rec.SetFaceNormal(r, outward_normal);
    rec.mat_ptr = mat_ptr;

    return true;
}

bool MovingSphere::BoundingBox(double _time0, double _time1, AABB& output_box) const
{
    AABB box0(
        GetCenter(_time0) - Vec3(radius, radius, radius),
        GetCenter(_time0) + Vec3(radius, radius, radius));
    AABB box1(
        GetCenter(_time1) - Vec3(radius, radius, radius),
        GetCenter(_time1) + Vec3(radius, radius, radius));
    output_box = SurroundingBox(box0, box1);
    return true;
}

Point3 MovingSphere::GetCenter(double time) const {
    return center0 + ((time - time0) / (time1 - time0)) * (center1 - center0);
}