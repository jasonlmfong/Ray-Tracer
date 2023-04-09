#include "Sphere.h"

__device__ Sphere::Sphere()
{
}

__device__ Sphere::Sphere(Point3 cen, float r, Material* m)
	: center(cen), radius(r), mat_ptr(m)
{
}

__device__ bool Sphere::Hit(const Ray& r, float t_min, float t_max, hitRecord& rec) const {
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
    rec.p = r.GetPointAtTime(rec.t);
    Vec3 outward_normal = (rec.p - center) / radius;
    rec.SetFaceNormal(r, outward_normal);
    GetSphereUV(outward_normal, rec.u, rec.v);
    rec.mat_ptr = mat_ptr;

    return true;
}

//__device__ bool Sphere::BoundingBox(float time0, float time1, AABB& output_box) const
//{
//    output_box = AABB(
//        center - Vec3(radius, radius, radius),
//        center + Vec3(radius, radius, radius));
//    return true;
//}

__device__ void Sphere::GetSphereUV(const Point3& p, float& u, float& v)
{
    // p: a given point on the sphere of radius one, centered at the origin.
    // u: returned value [0,1] of angle around the Y axis from X=-1.
    // v: returned value [0,1] of angle from Y=-1 to Y=+1.
    //     <1 0 0> yields <0.50 0.50>       <-1  0  0> yields <0.00 0.50>
    //     <0 1 0> yields <0.50 1.00>       < 0 -1  0> yields <0.50 0.00>
    //     <0 0 1> yields <0.25 0.50>       < 0  0 -1> yields <0.75 0.50>

    auto theta = acos(-p.y());
    auto phi = atan2(-p.z(), p.x()) + PI;

    u = phi / (2 * PI);
    v = theta / PI;
}
