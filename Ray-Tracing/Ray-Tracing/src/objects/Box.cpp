#include "Box.h"

Box::Box()
{
}

Box::Box(const Point3& p0, const Point3& p1, shared_ptr<Material> ptr)
{
    m_BoxMin = p0;
    m_BoxMax = p1;

    m_Sides.Add(make_shared<XYRect>(p0.x(), p1.x(), p0.y(), p1.y(), p1.z(), ptr));
    m_Sides.Add(make_shared<XYRect>(p0.x(), p1.x(), p0.y(), p1.y(), p0.z(), ptr));

    m_Sides.Add(make_shared<XZRect>(p0.x(), p1.x(), p0.z(), p1.z(), p1.y(), ptr));
    m_Sides.Add(make_shared<XZRect>(p0.x(), p1.x(), p0.z(), p1.z(), p0.y(), ptr));

    m_Sides.Add(make_shared<YZRect>(p0.y(), p1.y(), p0.z(), p1.z(), p1.x(), ptr));
    m_Sides.Add(make_shared<YZRect>(p0.y(), p1.y(), p0.z(), p1.z(), p0.x(), ptr));
}

bool Box::Hit(const Ray& r, double t_min, double t_max, hitRecord& rec) const {
    return m_Sides.Hit(r, t_min, t_max, rec);
}

bool Box::BoundingBox(double time0, double time1, AABB& output_Box) const
{
    output_Box = AABB(m_BoxMin, m_BoxMax);
    return true;
}