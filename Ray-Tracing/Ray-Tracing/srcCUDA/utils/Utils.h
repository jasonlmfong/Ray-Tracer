#pragma once
#ifndef UTILS_H
#define UTILS_H

#include <curand_kernel.h>
#include "Vec3.h"

// Constant
#ifndef PI
#define PI 3.14159265358979323846
#endif

__host__ __device__ inline double DegreesToRadians(double degrees) {
    return degrees * PI / 180.0;
}

__device__ inline Vec3 Reflect(const Vec3& v, const Vec3& n)
{
    return v - 2.0f * Dot(v, n) * n;
}

__device__ inline Vec3 Refract(const Vec3& uv, const Vec3& n, float etai_over_etat) {
    auto cos_theta = fmin(Dot(-uv, n), 1.0f);
    Vec3 r_out_perp = etai_over_etat * (uv + cos_theta * n);
    Vec3 r_out_parallel = -sqrt(fabs(1.0f - r_out_perp.LengthSquared())) * n;
    return r_out_perp + r_out_parallel;
}

__device__ inline double clamp(double x, double min, double max) {
    if (x < min) return min;
    if (x > max) return max;
    return x;
}

__device__ inline float RandomDouble(curandState* local_rand_state)
{
    // Returns a random real in [0,1).
    return curand_uniform(local_rand_state);
}

__device__ inline float RandomDoubleBetween(float min, float max, curandState* local_rand_state)
{
    // Returns a random real in [min,max).
    return min + (max - min) * RandomDouble(local_rand_state);
}

__device__ inline Vec3 RandomVec3(curandState* local_rand_state)
{
    return Vec3(RandomDouble(local_rand_state), RandomDouble(local_rand_state), RandomDouble(local_rand_state));
}

__device__ inline Vec3 RandomVec3Between(float min, float max, curandState* local_rand_state)
{
    return Vec3(RandomDoubleBetween(min, max, local_rand_state), RandomDoubleBetween(min, max, local_rand_state), RandomDoubleBetween(min, max, local_rand_state));
}

__device__ inline Vec3 RandomInUnitCube(curandState* local_rand_state)
{
    return RandomVec3Between(-1, 1, local_rand_state);
}

__device__ inline Vec3 RandomUnitVector(curandState* local_rand_state) {
    return UnitVector(RandomInUnitCube(local_rand_state));
}

__device__ inline Vec3 RandomInUnitDisk(curandState* local_rand_state) 
{
    Vec3 p;
    do {
        p = 2.0f * Vec3(curand_uniform(local_rand_state), curand_uniform(local_rand_state), 0) - Vec3(1, 1, 0);
    } while (Dot(p, p) >= 1.0f);
    return p;
}

__device__ inline int RandomInt(int min, int max, curandState* local_rand_state) {
    // Returns a random integer in [min,max].
    return static_cast<int>(RandomDoubleBetween(min, max + 1, local_rand_state));
}

#endif