#include "AABB.h"

AABB::AABB()
{
}

AABB::AABB(const Point3& a, const Point3& b)
{
	minimum = a; maximum = b;
}

Point3 AABB::Min() const
{
	return minimum;
}

Point3 AABB::Max() const
{
	return maximum;
}

bool AABB::Hit(const Ray& r, double t_min, double t_max) const
{
    for (int a = 0; a < 3; a++) {
        auto invD = 1.0f / r.GetDirection()[a];
        auto t0 = (Min()[a] - r.GetOrigin()[a]) * invD;
        auto t1 = (Max()[a] - r.GetOrigin()[a]) * invD;
        if (invD < 0.0f)
            std::swap(t0, t1);
        t_min = t0 > t_min ? t0 : t_min;
        t_max = t1 < t_max ? t1 : t_max;
        if (t_max <= t_min)
            return false;
    }
    return true;
}
