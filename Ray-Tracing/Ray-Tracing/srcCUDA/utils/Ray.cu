#include "Ray.h"

__device__ Ray::Ray()
{
}

__device__ Ray::Ray(const Vec3& origin, const Vec3& direction, const float time = 0.0)
	: m_Orig(origin), m_Dir(direction), m_Time(time)
{
}

__device__ Vec3 Ray::GetOrigin() const
{
	return m_Orig;
}

__device__ Vec3 Ray::GetDirection() const
{
	return m_Dir;
}

__device__ float Ray::GetTime() const
{
	return m_Time;
}

__device__ Vec3 Ray::GetPointAtTime(float t) const
{
	return m_Orig + t * m_Dir;
}
