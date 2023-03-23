#pragma once
#ifndef RAY_H
#define RAY_H

//#include "vendor/glm/ext/vector_double3.hpp"
#include "vec3.h"

class Ray {
public:
    Ray();
    Ray(const vec3& origin, const vec3& direction);

    vec3 GetOrigin() const;
    vec3 GetDirection() const;

    vec3 GetPosAtDir(double t) const;

private:
    vec3 m_Orig;
    vec3 m_Dir;
};

#endif