#include "Rotate.h"

RotateX::RotateX(shared_ptr<Hittable> p, double angle)
    : m_Ptr(p)
{
    auto radians = degreesToRadians(angle);
    m_SinTheta = sin(radians);
    m_CosTheta = cos(radians);
    m_HasBox = m_Ptr->BoundingBox(0, 1, m_BoundBox);

    Point3 min(infinity, infinity, infinity);
    Point3 max(-infinity, -infinity, -infinity);

    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            for (int k = 0; k < 2; k++) {
                auto x = i * m_BoundBox.Max().x() + (1 - i) * m_BoundBox.Min().x();
                auto y = j * m_BoundBox.Max().y() + (1 - j) * m_BoundBox.Min().y();
                auto z = k * m_BoundBox.Max().z() + (1 - k) * m_BoundBox.Min().z();

                auto newy = m_CosTheta * y - m_SinTheta * z;
                auto newz = m_SinTheta * y + m_CosTheta * z;

                Vec3 tester(x, newy, newz);

                for (int c = 0; c < 3; c++) {
                    min[c] = fmin(min[c], tester[c]);
                    max[c] = fmax(max[c], tester[c]);
                }
            }
        }
    }

    m_BoundBox = AABB(min, max);
}

bool RotateX::Hit(const Ray& r, double t_min, double t_max, hitRecord& rec) const
{
    auto origin = r.GetOrigin();
    auto direction = r.GetDirection();

    origin[1] = m_CosTheta * r.GetOrigin()[1] - m_SinTheta * r.GetOrigin()[2];
    origin[2] = m_SinTheta * r.GetOrigin()[1] + m_CosTheta * r.GetOrigin()[2];

    direction[1] = m_CosTheta * r.GetDirection()[1] - m_SinTheta * r.GetDirection()[2];
    direction[2] = m_SinTheta * r.GetDirection()[1] + m_CosTheta * r.GetDirection()[2];

    Ray rotated_r(origin, direction, r.GetTime());

    if (!m_Ptr->Hit(rotated_r, t_min, t_max, rec))
        return false;

    auto p = rec.p;
    auto normal = rec.normal;

    p[1] = m_CosTheta * rec.p[1] + m_SinTheta * rec.p[2];
    p[2] = -m_SinTheta * rec.p[1] + m_CosTheta * rec.p[2];

    normal[1] = m_CosTheta * rec.normal[1] + m_SinTheta * rec.normal[2];
    normal[2] = -m_SinTheta * rec.normal[1] + m_CosTheta * rec.normal[2];

    rec.p = p;
    rec.SetFaceNormal(rotated_r, normal);

    return true;
}

bool RotateX::BoundingBox(double time0, double time1, AABB& output_box) const
{
    output_box = m_BoundBox;
    return m_HasBox;
}

RotateY::RotateY(shared_ptr<Hittable> p, double angle)
    : m_Ptr(p)
{
    auto radians = degreesToRadians(angle);
    m_SinTheta = sin(radians);
    m_CosTheta = cos(radians);
    m_HasBox = m_Ptr->BoundingBox(0, 1, m_BoundBox);

    Point3 min(infinity, infinity, infinity);
    Point3 max(-infinity, -infinity, -infinity);

    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            for (int k = 0; k < 2; k++) {
                auto x = i * m_BoundBox.Max().x() + (1 - i) * m_BoundBox.Min().x();
                auto y = j * m_BoundBox.Max().y() + (1 - j) * m_BoundBox.Min().y();
                auto z = k * m_BoundBox.Max().z() + (1 - k) * m_BoundBox.Min().z();

                auto newx = m_CosTheta * x + m_SinTheta * z;
                auto newz = -m_SinTheta * x + m_CosTheta * z;

                Vec3 tester(newx, y, newz);

                for (int c = 0; c < 3; c++) {
                    min[c] = fmin(min[c], tester[c]);
                    max[c] = fmax(max[c], tester[c]);
                }
            }
        }
    }

    m_BoundBox = AABB(min, max);
}

bool RotateY::Hit(const Ray& r, double t_min, double t_max, hitRecord& rec) const
{
    auto origin = r.GetOrigin();
    auto direction = r.GetDirection();

    origin[0] = m_CosTheta * r.GetOrigin()[0] - m_SinTheta * r.GetOrigin()[2];
    origin[2] = m_SinTheta * r.GetOrigin()[0] + m_CosTheta * r.GetOrigin()[2];

    direction[0] = m_CosTheta * r.GetDirection()[0] - m_SinTheta * r.GetDirection()[2];
    direction[2] = m_SinTheta * r.GetDirection()[0] + m_CosTheta * r.GetDirection()[2];

    Ray rotated_r(origin, direction, r.GetTime());

    if (!m_Ptr->Hit(rotated_r, t_min, t_max, rec))
        return false;

    auto p = rec.p;
    auto normal = rec.normal;

    p[0] = m_CosTheta * rec.p[0] + m_SinTheta * rec.p[2];
    p[2] = -m_SinTheta * rec.p[0] + m_CosTheta * rec.p[2];

    normal[0] = m_CosTheta * rec.normal[0] + m_SinTheta * rec.normal[2];
    normal[2] = -m_SinTheta * rec.normal[0] + m_CosTheta * rec.normal[2];

    rec.p = p;
    rec.SetFaceNormal(rotated_r, normal);

    return true;
}

bool RotateY::BoundingBox(double time0, double time1, AABB& output_box) const
{
    output_box = m_BoundBox;
    return m_HasBox;
}

RotateZ::RotateZ(shared_ptr<Hittable> p, double angle)
    : m_Ptr(p)
{
    auto radians = degreesToRadians(angle);
    m_SinTheta = sin(radians);
    m_CosTheta = cos(radians);
    m_HasBox = m_Ptr->BoundingBox(0, 1, m_BoundBox);

    Point3 min(infinity, infinity, infinity);
    Point3 max(-infinity, -infinity, -infinity);

    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            for (int k = 0; k < 2; k++) {
                auto x = i * m_BoundBox.Max().x() + (1 - i) * m_BoundBox.Min().x();
                auto y = j * m_BoundBox.Max().y() + (1 - j) * m_BoundBox.Min().y();
                auto z = k * m_BoundBox.Max().z() + (1 - k) * m_BoundBox.Min().z();

                auto newx = m_CosTheta * x + m_SinTheta * y;
                auto newy = -m_SinTheta * x + m_CosTheta * y;

                Vec3 tester(newx, newy, z);

                for (int c = 0; c < 3; c++) {
                    min[c] = fmin(min[c], tester[c]);
                    max[c] = fmax(max[c], tester[c]);
                }
            }
        }
    }

    m_BoundBox = AABB(min, max);
}

bool RotateZ::Hit(const Ray& r, double t_min, double t_max, hitRecord& rec) const
{
    auto origin = r.GetOrigin();
    auto direction = r.GetDirection();

    origin[0] = m_CosTheta * r.GetOrigin()[0] - m_SinTheta * r.GetOrigin()[1];
    origin[1] = m_SinTheta * r.GetOrigin()[0] + m_CosTheta * r.GetOrigin()[1];

    direction[0] = m_CosTheta * r.GetDirection()[0] - m_SinTheta * r.GetDirection()[1];
    direction[1] = m_SinTheta * r.GetDirection()[0] + m_CosTheta * r.GetDirection()[1];

    Ray rotated_r(origin, direction, r.GetTime());

    if (!m_Ptr->Hit(rotated_r, t_min, t_max, rec))
        return false;

    auto p = rec.p;
    auto normal = rec.normal;

    p[0] = m_CosTheta * rec.p[0] + m_SinTheta * rec.p[1];
    p[1] = -m_SinTheta * rec.p[0] + m_CosTheta * rec.p[1];

    normal[0] = m_CosTheta * rec.normal[0] + m_SinTheta * rec.normal[1];
    normal[1] = -m_SinTheta * rec.normal[0] + m_CosTheta * rec.normal[1];

    rec.p = p;
    rec.SetFaceNormal(rotated_r, normal);

    return true;
}

bool RotateZ::BoundingBox(double time0, double time1, AABB& output_box) const
{
    output_box = m_BoundBox;
    return m_HasBox;
}