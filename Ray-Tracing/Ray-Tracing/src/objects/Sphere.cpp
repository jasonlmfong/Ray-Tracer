#include "Sphere.h"

Sphere::Sphere()
{
}

Sphere::Sphere(Point3 cen, double r, shared_ptr<Material> m)
    : center(cen), radius(r), mat_ptr(m) 
{
}

bool Sphere::Hit(const Ray& r, double t_min, double t_max, hitRecord& rec) const
{
    Vec3 oc = r.GetOrigin() - center;
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
    Vec3 outward_normal = (rec.p - center) / radius;
    rec.SetFaceNormal(r, outward_normal);
    rec.mat_ptr = mat_ptr;

    return true;
}