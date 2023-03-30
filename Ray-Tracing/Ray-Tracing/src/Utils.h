#pragma once
#ifndef UTILS_H
#define UTILS_H

#include <cmath>
#include <limits>
#include <memory>
#include <cstdlib>

#include "Ray.h"
#include "Vec3.h"

// Usings

using std::shared_ptr;
using std::make_shared;
using std::sqrt;

// Constants

const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.1415926535897932385;

// Utility Functions

inline double degreesToRadians(double degrees) {
    return degrees * pi / 180.0;
}

inline Vec3 reflect(const Vec3& v, const Vec3& n) {
    return v - 2 * Dot(v, n) * n;
}

inline Vec3 refract(const Vec3& uv, const Vec3& n, double etai_over_etat) {
    auto cos_theta = fmin(Dot(-uv, n), 1.0);
    Vec3 r_out_perp = etai_over_etat * (uv + cos_theta * n);
    Vec3 r_out_parallel = -sqrt(fabs(1.0 - r_out_perp.LengthSquared())) * n;
    return r_out_perp + r_out_parallel;
}

inline double clamp(double x, double min, double max) {
    if (x < min) return min;
    if (x > max) return max;
    return x;
}

inline Vec3 UnitVector(Vec3 v) {
    return v / v.Length();
}

inline double RandomDouble() {
    // Returns a random real in [0,1).
    return rand() / (RAND_MAX + 1.0);
}

inline double RandomDouble(double min, double max) {
    // Returns a random real in [min,max).
    return min + (max - min) * RandomDouble();
}

inline static Vec3 RandomVec3() {
    return Vec3(RandomDouble(), RandomDouble(), RandomDouble());
}

inline static Vec3 RandomVec3(double min, double max) {
    return Vec3(RandomDouble(min, max), RandomDouble(min, max), RandomDouble(min, max));
}

inline Vec3 RandomInUnitCube() {
    while (true) {
        auto p = RandomVec3(-1, 1);
        if (p.LengthSquared() >= 1) continue;
        return p;
    }
}

inline Vec3 RandomUnitVector() {
    return UnitVector(RandomInUnitCube());
}

inline Vec3 RandomInUnitDisk() {
    while (true) {
        auto p = Vec3(RandomDouble(-1, 1), RandomDouble(-1, 1), 0);
        if (p.LengthSquared() >= 1) continue;
        return p;
    }
}

inline int RandomInt(int min, int max) {
    // Returns a random integer in [min,max].
    return static_cast<int>(RandomDouble(min, max + 1));
}

#endif