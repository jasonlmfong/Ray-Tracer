#pragma once
#ifndef RAY_H
#define RAY_H

#include "Vec3.h"

class Ray
{
public:
    __device__ Ray();
    __device__ Ray(const Point3& origin, const Vec3& direction, const float time);

    __device__ Point3 GetOrigin()  const;
    __device__ Vec3 GetDirection() const;
    __device__ float GetTime() const;

    __device__ Point3 GetPointAtTime(float t) const;

private:
    Point3 m_Orig;
    Vec3 m_Dir;
    float m_Time;
};

#endif
