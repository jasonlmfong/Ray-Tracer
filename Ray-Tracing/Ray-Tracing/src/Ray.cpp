#include "Ray.h"

Ray::Ray() {}

Ray::Ray(const vec3& origin, const vec3& direction, double time = 0.0)
    : m_Orig(origin), m_Dir(direction), m_Time(time)
{
}

vec3 Ray::GetOrigin() const
{ 
    return m_Orig; 
}

vec3 Ray::GetDirection() const
{ 
    return m_Dir; 
}

double Ray::GetTime() const
{
    return m_Time;
}

vec3 Ray::GetPosAtDir(double t) const
{
    return m_Orig + t * m_Dir;
}