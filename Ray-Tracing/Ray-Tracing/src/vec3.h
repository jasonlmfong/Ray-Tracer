#pragma once
#ifndef Vec3_H
#define Vec3_H

#include <cmath>
#include <iostream>

using std::sqrt;

class Vec3 {
public:
    Vec3();
    Vec3(double e0, double e1, double e2);

    double x() const;
    double y() const;
    double z() const;

    Vec3 operator-() const;
    double operator[](int i) const;
    double& operator[](int i);

    Vec3& operator+=(const Vec3& v);

    Vec3& operator*=(const double t);

    Vec3& operator/=(const double t);

    double Length() const;

    double LengthSquared() const;

    bool NearZero() const;

public:
    double e[3];
};

// Type aliases for Vec3
using Point3 = Vec3;   // 3D point
using Color = Vec3;    // RGB color

#endif

// Vec3 Utility Functions

inline std::ostream& operator<<(std::ostream& out, const Vec3& v) {
    return out << v.e[0] << ' ' << v.e[1] << ' ' << v.e[2];
}

inline Vec3 operator+(const Vec3& u, const Vec3& v) {
    return Vec3(u.e[0] + v.e[0], u.e[1] + v.e[1], u.e[2] + v.e[2]);
}

inline Vec3 operator-(const Vec3& u, const Vec3& v) {
    return Vec3(u.e[0] - v.e[0], u.e[1] - v.e[1], u.e[2] - v.e[2]);
}

inline Vec3 operator*(const Vec3& u, const Vec3& v) {
    return Vec3(u.e[0] * v.e[0], u.e[1] * v.e[1], u.e[2] * v.e[2]);
}

inline Vec3 operator*(double t, const Vec3& v) {
    return Vec3(t * v.e[0], t * v.e[1], t * v.e[2]);
}

inline Vec3 operator*(const Vec3& v, double t) {
    return t * v;
}

inline Vec3 operator/(Vec3 v, double t) {
    return (1 / t) * v;
}

inline double Dot(const Vec3& u, const Vec3& v) {
    return u.e[0] * v.e[0]
        + u.e[1] * v.e[1]
        + u.e[2] * v.e[2];
}

inline Vec3 Cross(const Vec3& u, const Vec3& v) {
    return Vec3(u.e[1] * v.e[2] - u.e[2] * v.e[1],
        u.e[2] * v.e[0] - u.e[0] * v.e[2],
        u.e[0] * v.e[1] - u.e[1] * v.e[0]);
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