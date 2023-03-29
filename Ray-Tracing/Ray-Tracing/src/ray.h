#pragma once
#ifndef RAY_H
#define RAY_H

//#include "vendor/glm/ext/vector_double3.hpp"
#include "vec3.h"

class Ray {
public:
    Ray();
    Ray(const vec3& origin, const vec3& direction, double time);

    vec3 GetOrigin() const;
    vec3 GetDirection() const;
    double GetTime() const;

    vec3 GetPosAtDir(double t) const;

private:
    vec3 m_Orig;
    vec3 m_Dir;
    double m_Time;
};

#endif