#include "Vec3.h"

__host__ __device__ Vec3::Vec3()
    : e{ 0, 0, 0 }
{
}

__host__ __device__ Vec3::Vec3(float e0, float e1, float e2)
    : e{ e0, e1, e2 }
{
}

__host__ __device__ float Vec3::x() const
{
    return e[0];
}

__host__ __device__ float Vec3::y() const
{
    return e[1];
}

__host__ __device__ float Vec3::z() const
{
    return e[2];
}

__host__ __device__ Vec3 Vec3::operator-() const
{
    return Vec3(-e[0], -e[1], -e[2]);
}

__host__ __device__ float Vec3::operator[](int i) const
{
    return e[i];
}

__host__ __device__ float& Vec3::operator[](int i) {
    return e[i];
}

__host__ __device__ Vec3& Vec3::operator+=(const Vec3& v2)
{
    e[0] += v2.e[0];
    e[1] += v2.e[1];
    e[2] += v2.e[2];
    return *this;
}

__host__ __device__ Vec3& Vec3::operator*=(const Vec3& v2)
{
    e[0] *= v2.e[0];
    e[1] *= v2.e[1];
    e[2] *= v2.e[2];
    return *this;
}

__host__ __device__ Vec3& Vec3::operator/=(const Vec3& v2)
{
    e[0] /= v2.e[0];
    e[1] /= v2.e[1];
    e[2] /= v2.e[2];
    return *this;
}

__host__ __device__ Vec3& Vec3::operator-=(const Vec3& v2)
{
    e[0] -= v2.e[0];
    e[1] -= v2.e[1];
    e[2] -= v2.e[2];
    return *this;
}

__host__ __device__ Vec3& Vec3::operator*=(const float t)
{
    e[0] *= t;
    e[1] *= t;
    e[2] *= t;
    return *this;
}

__host__ __device__ Vec3& Vec3::operator/=(const float t)
{
    float k = 1.0 / t;

    e[0] *= k;
    e[1] *= k;
    e[2] *= k;
    return *this;
}

__host__ __device__ float Vec3::Length() const 
{ 
    return sqrt(e[0] * e[0] + e[1] * e[1] + e[2] * e[2]); 
}

__host__ __device__ float Vec3::LengthSquared() const
{ 
    return e[0] * e[0] + e[1] * e[1] + e[2] * e[2]; 
}

__host__ __device__ bool Vec3::NearZero() const
{
    // Return true if the vector is close to zero in all dimensions.
    const auto s = 1e-8;
    return (fabs(e[0]) < s) && (fabs(e[1]) < s) && (fabs(e[2]) < s);
}

__host__ __device__ void Vec3::MakeUnitVector()
{
    float k = 1.0 / sqrt(e[0] * e[0] + e[1] * e[1] + e[2] * e[2]);
    e[0] *= k; e[1] *= k; e[2] *= k;
}