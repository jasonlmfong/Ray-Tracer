#pragma once
#ifndef VEC3_H
#define VEC3_H

#include <cmath>
#include <iostream>

using std::sqrt;

class vec3 {
public:
    vec3();
    vec3(double e0, double e1, double e2);

    double x() const;
    double y() const;
    double z() const;

    vec3 operator-() const;
    double operator[](int i) const;
    double& operator[](int i);

    vec3& operator+=(const vec3& v);

    vec3& operator*=(const double t);

    vec3& operator/=(const double t);

    double length() const;

    double lengthSquared() const;

    bool nearZero() const;

public:
    double e[3];
};

// Type aliases for vec3
using Point3 = vec3;   // 3D point
using Color = vec3;    // RGB color

#endif

// vec3 Utility Functions

inline std::ostream& operator<<(std::ostream& out, const vec3& v) {
    return out << v.e[0] << ' ' << v.e[1] << ' ' << v.e[2];
}

inline vec3 operator+(const vec3& u, const vec3& v) {
    return vec3(u.e[0] + v.e[0], u.e[1] + v.e[1], u.e[2] + v.e[2]);
}

inline vec3 operator-(const vec3& u, const vec3& v) {
    return vec3(u.e[0] - v.e[0], u.e[1] - v.e[1], u.e[2] - v.e[2]);
}

inline vec3 operator*(const vec3& u, const vec3& v) {
    return vec3(u.e[0] * v.e[0], u.e[1] * v.e[1], u.e[2] * v.e[2]);
}

inline vec3 operator*(double t, const vec3& v) {
    return vec3(t * v.e[0], t * v.e[1], t * v.e[2]);
}

inline vec3 operator*(const vec3& v, double t) {
    return t * v;
}

inline vec3 operator/(vec3 v, double t) {
    return (1 / t) * v;
}

inline double dot(const vec3& u, const vec3& v) {
    return u.e[0] * v.e[0]
        + u.e[1] * v.e[1]
        + u.e[2] * v.e[2];
}

inline vec3 cross(const vec3& u, const vec3& v) {
    return vec3(u.e[1] * v.e[2] - u.e[2] * v.e[1],
        u.e[2] * v.e[0] - u.e[0] * v.e[2],
        u.e[0] * v.e[1] - u.e[1] * v.e[0]);
}

inline vec3 unitVector(vec3 v) {
    return v / v.length();
}

inline double randomDouble() {
    // Returns a random real in [0,1).
    return rand() / (RAND_MAX + 1.0);
}

inline double randomDouble(double min, double max) {
    // Returns a random real in [min,max).
    return min + (max - min) * randomDouble();
}

inline static vec3 randomVec3() {
    return vec3(randomDouble(), randomDouble(), randomDouble());
}

inline static vec3 randomVec3(double min, double max) {
    return vec3(randomDouble(min, max), randomDouble(min, max), randomDouble(min, max));
}

inline vec3 randomInUnitCube() {
    while (true) {
        auto p = randomVec3(-1, 1);
        if (p.lengthSquared() >= 1) continue;
        return p;
    }
}

inline vec3 randomUnitVector() {
    return unitVector(randomInUnitCube());
}

inline vec3 randomInUnitDisk() {
    while (true) {
        auto p = vec3(randomDouble(-1, 1), randomDouble(-1, 1), 0);
        if (p.lengthSquared() >= 1) continue;
        return p;
    }
}