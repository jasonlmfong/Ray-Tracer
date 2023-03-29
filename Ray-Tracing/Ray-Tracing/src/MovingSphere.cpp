#include "MovingSphere.h"

MovingSphere::MovingSphere()
{
}

MovingSphere::MovingSphere(Point3 cen0, Point3 cen1, double _time0, double _time1, double r, shared_ptr<Material> m)
	: center0(cen0), center1(cen1), time0(_time0), time1(_time1), radius(r), mat_ptr(m)
{
}

bool MovingSphere::hit(const Ray& r, double t_min, double t_max, hitRecord& rec) const 
{
    vec3 oc = r.GetOrigin() - center(r.GetTime());
    auto a = r.GetDirection().lengthSquared();
    auto half_b = dot(oc, r.GetDirection());
    auto c = oc.lengthSquared() - radius * radius;

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
    auto outward_normal = (rec.p - center(r.GetTime())) / radius;
    rec.setFaceNormal(r, outward_normal);
    rec.mat_ptr = mat_ptr;

    return true;
}

Point3 MovingSphere::center(double time) const {
    return center0 + ((time - time0) / (time1 - time0)) * (center1 - center0);
}