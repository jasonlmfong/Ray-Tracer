#include "AARect.h"

XYRect::XYRect()
{
}

XYRect::XYRect(double _x0, double _x1, double _y0, double _y1, double _z, shared_ptr<Material> mat)
    : x0(_x0), x1(_x1), y0(_y0), y1(_y1), z(_z), matPtr(mat) 
{
}

bool XYRect::Hit(const Ray& r, double t_min, double t_max, hitRecord& rec) const
{
    auto t = (z - r.GetOrigin().z()) / r.GetDirection().z();
    if (t < t_min || t > t_max)
        return false;
    auto x = r.GetOrigin().x() + t * r.GetDirection().x();
    auto y = r.GetOrigin().y() + t * r.GetDirection().y();
    if (x < x0 || x > x1 || y < y0 || y > y1)
        return false;
    rec.u = (x - x0) / (x1 - x0);
    rec.v = (y - y0) / (y1 - y0);
    rec.t = t;
    auto outward_normal = Vec3(0, 0, 1);
    rec.SetFaceNormal(r, outward_normal);
    rec.mat_ptr = matPtr;
    rec.p = r.GetPosAtDir(t);
    return true;
}

bool XYRect::BoundingBox(double time0, double time1, AABB& output_box) const
{
    // The bounding box must have non-zero width in each dimension, so pad the Z
    // dimension a small amount.
    output_box = AABB(Point3(x0, y0, z - 0.0001), Point3(x1, y1, z + 0.0001));
    return true;
}

XZRect::XZRect()
{
}

XZRect::XZRect(double _x0, double _x1, double _z0, double _z1, double _y, shared_ptr<Material> mat)
    : x0(_x0), x1(_x1), z0(_z0), z1(_z1), y(_y), matPtr(mat) 
{
}

bool XZRect::Hit(const Ray& r, double t_min, double t_max, hitRecord& rec) const
{
    auto t = (y - r.GetOrigin().y()) / r.GetDirection().y();
    if (t < t_min || t > t_max)
        return false;
    auto x = r.GetOrigin().x() + t * r.GetDirection().x();
    auto z = r.GetOrigin().z() + t * r.GetDirection().z();
    if (x < x0 || x > x1 || z < z0 || z > z1)
        return false;
    rec.u = (x - x0) / (x1 - x0);
    rec.v = (z - z0) / (z1 - z0);
    rec.t = t;
    auto outward_normal = Vec3(0, 1, 0);
    rec.SetFaceNormal(r, outward_normal);
    rec.mat_ptr = matPtr;
    rec.p = r.GetPosAtDir(t);
    return true;
}

bool XZRect::BoundingBox(double time0, double time1, AABB& output_box) const
{
    // The bounding box must have non-zero width in each dimension, so pad the Y
    // dimension a small amount.
    output_box = AABB(Point3(x0, y - 0.0001, z0), Point3(x1, y + 0.0001, z1));
    return true;
}

YZRect::YZRect()
{
}

YZRect::YZRect(double _y0, double _y1, double _z0, double _z1, double _x, shared_ptr<Material> mat)
    : y0(_y0), y1(_y1), z0(_z0), z1(_z1), x(_x), matPtr(mat)
{
}

bool YZRect::Hit(const Ray& r, double t_min, double t_max, hitRecord& rec) const
{
    auto t = (x - r.GetOrigin().x()) / r.GetDirection().x();
    if (t < t_min || t > t_max)
        return false;
    auto y = r.GetOrigin().y() + t * r.GetDirection().y();
    auto z = r.GetOrigin().z() + t * r.GetDirection().z();
    if (y < y0 || y > y1 || z < z0 || z > z1)
        return false;
    rec.u = (y - y0) / (y1 - y0);
    rec.v = (z - z0) / (z1 - z0);
    rec.t = t;
    auto outward_normal = Vec3(1, 0, 0);
    rec.SetFaceNormal(r, outward_normal);
    rec.mat_ptr = matPtr;
    rec.p = r.GetPosAtDir(t);
    return true;
}

bool YZRect::BoundingBox(double time0, double time1, AABB& output_box) const
{
    // The bounding box must have non-zero width in each dimension, so pad the X
    // dimension a small amount.
    output_box = AABB(Point3(x - 0.0001, y0, z0), Point3(x + 0.0001, y1, z1));
    return true;
}