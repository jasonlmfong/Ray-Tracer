#include "Ray.h"

Ray::Ray() {}

Ray::Ray(const vec3& origin, const vec3& direction)
    : m_Orig(origin), m_Dir(direction)
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

vec3 Ray::GetPosAtDir(double t) const
{
    return m_Orig + t * m_Dir;
}