#include "Ray.h"

Ray::Ray() {}

Ray::Ray(const Vec3& origin, const Vec3& direction, double time = 0.0)
    : m_Orig(origin), m_Dir(direction), m_Time(time)
{
}

Vec3 Ray::GetOrigin() const
{ 
    return m_Orig; 
}

Vec3 Ray::GetDirection() const
{ 
    return m_Dir; 
}

double Ray::GetTime() const
{
    return m_Time;
}

Vec3 Ray::GetPosAtDir(double t) const
{
    return m_Orig + t * m_Dir;
}