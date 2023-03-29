#include "Sphere.h"

Sphere::Sphere()
{
}

Sphere::Sphere(Point3 cen, double r, shared_ptr<Material> m)
    : center(cen), radius(r), mat_ptr(m) 
{
}

bool Sphere::hit(const Ray& r, double t_min, double t_max, hitRecord& rec) const
{
    vec3 oc = r.GetOrigin() - center;
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
    vec3 outward_normal = (rec.p - center) / radius;
    rec.setFaceNormal(r, outward_normal);
    rec.mat_ptr = mat_ptr;

    return true;
}