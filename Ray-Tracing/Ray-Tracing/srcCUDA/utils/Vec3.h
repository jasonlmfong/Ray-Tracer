#pragma once
#ifndef VEC3_H
#define VEC3_H

#include <math.h>
#include <stdlib.h>
#include <iostream>

class Vec3  {
public:
    __host__ __device__ Vec3();
    __host__ __device__ Vec3(float e0, float e1, float e2);
    __host__ __device__ float x() const;
    __host__ __device__ float y() const;
    __host__ __device__ float z() const;

    __host__ __device__ Vec3 operator-() const;
    __host__ __device__ float operator[](int i) const;
    __host__ __device__ float& operator[](int i);

    __host__ __device__ Vec3& operator+=(const Vec3 &v2);
    __host__ __device__ Vec3& operator-=(const Vec3 &v2);
    __host__ __device__ Vec3& operator*=(const Vec3 &v2);
    __host__ __device__ Vec3& operator/=(const Vec3 &v2);
    __host__ __device__ Vec3& operator*=(const float t);
    __host__ __device__ Vec3& operator/=(const float t);

    __host__ __device__ float Length() const;
    __host__ __device__ float LengthSquared() const;
    __host__ __device__ bool NearZero() const;
    __host__ __device__ void MakeUnitVector();

public:
    float e[3];
};

// Type aliases for Vec3
using Point3 = Vec3;   // 3D point
using Color = Vec3;    // RGB color


__host__ __device__ inline Vec3 operator+(const Vec3 &v1, const Vec3 &v2) 
{
    return Vec3(v1.e[0] + v2.e[0], v1.e[1] + v2.e[1], v1.e[2] + v2.e[2]);
}

__host__ __device__ inline Vec3 operator-(const Vec3 &v1, const Vec3 &v2) 
{
    return Vec3(v1.e[0] - v2.e[0], v1.e[1] - v2.e[1], v1.e[2] - v2.e[2]);
}

__host__ __device__ inline Vec3 operator*(const Vec3 &v1, const Vec3 &v2) 
{
    return Vec3(v1.e[0] * v2.e[0], v1.e[1] * v2.e[1], v1.e[2] * v2.e[2]);
}

__host__ __device__ inline Vec3 operator/(const Vec3 &v1, const Vec3 &v2) 
{
    return Vec3(v1.e[0] / v2.e[0], v1.e[1] / v2.e[1], v1.e[2] / v2.e[2]);
}

__host__ __device__ inline Vec3 operator*(const Vec3& v, float t)
{
    return Vec3(t * v.e[0], t * v.e[1], t * v.e[2]);
}

__host__ __device__ inline Vec3 operator*(float t, const Vec3 &v) 
{
    return Vec3(t*v.e[0], t*v.e[1], t*v.e[2]);
}

__host__ __device__ inline Vec3 operator/(Vec3 v, float t) 
{
    return Vec3(v.e[0]/t, v.e[1]/t, v.e[2]/t);
}

__host__ __device__ inline float Dot(const Vec3 &v1, const Vec3 &v2) 
{
    return v1.e[0] *v2.e[0] + v1.e[1] *v2.e[1]  + v1.e[2] *v2.e[2];
}

__host__ __device__ inline Vec3 Cross(const Vec3 &v1, const Vec3 &v2) 
{
    return Vec3( (v1.e[1]*v2.e[2] - v1.e[2]*v2.e[1]),
                (-(v1.e[0]*v2.e[2] - v1.e[2]*v2.e[0])),
                (v1.e[0]*v2.e[1] - v1.e[1]*v2.e[0]));
}

__host__ __device__ inline Vec3 UnitVector(Vec3 v)
{
    return v / v.Length();
}

#endif