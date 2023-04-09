#include "AABB.h"

__device__ AABB::AABB()
{
}

__device__ AABB::AABB(const Point3& a, const Point3& b)
{
    minimum = a; maximum = b;
}

__device__ Point3 AABB::Min() const
{
    return minimum;
}

__device__ Point3 AABB::Max() const
{
    return maximum;
}

__device__ bool AABB::Hit(const Ray& r, float t_min, float t_max) const
{
    for (int a = 0; a < 3; a++) {
        auto invD = 1.0f / r.GetDirection()[a];
        auto t0 = (Min()[a] - r.GetOrigin()[a]) * invD;
        auto t1 = (Max()[a] - r.GetOrigin()[a]) * invD;
        if (invD < 0.0f)
        {   // replace std::swap
            float temp = t0;
            t0 = t1;
            t1 = temp;
        }
        t_min = t0 > t_min ? t0 : t_min;
        t_max = t1 < t_max ? t1 : t_max;
        if (t_max <= t_min)
            return false;
    }
    return true;
}
