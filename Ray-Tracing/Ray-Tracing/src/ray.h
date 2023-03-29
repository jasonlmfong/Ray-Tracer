#pragma once
#ifndef RAY_H
#define RAY_H

//#include "vendor/glm/ext/vector_double3.hpp"
#include "Vec3.h"

class Ray {
public:
    Ray();
    Ray(const Vec3& origin, const Vec3& direction, double time);

    Vec3 GetOrigin() const;
    Vec3 GetDirection() const;
    double GetTime() const;

    Vec3 GetPosAtDir(double t) const;

private:
    Vec3 m_Orig;
    Vec3 m_Dir;
    double m_Time;
};

#endif