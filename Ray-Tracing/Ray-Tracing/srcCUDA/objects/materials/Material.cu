#include "Material.h"

__device__ bool Material::Scatter(const Ray& r_in, const hitRecord& rec, Vec3& attenuation, Ray& Scattered, curandState* local_rand_state) const
{
    return false;
}

__device__ Lambertian::Lambertian(const Color& a)
    : albedo(&SolidColor(a))
{
}

__device__ Lambertian::Lambertian(Texture* a)
    : albedo(a)
{
}

__device__ bool Lambertian::Scatter(const Ray& r_in, const hitRecord& rec, Vec3& attenuation, Ray& Scattered, curandState* local_rand_state) const
{
    Vec3 scatter_direction = rec.normal + RandomUnitVector(local_rand_state);

    // Catch degenerate scatter direction
    if (scatter_direction.NearZero())
        scatter_direction = rec.normal;

    Scattered = Ray(rec.p, scatter_direction, r_in.GetTime());
    attenuation = albedo->GetValue(rec.u, rec.v, rec.p);
    return true;
}

__device__ Metal::Metal(const Vec3& a, float f)
    : albedo(a) 
{
    if (f < 1) fuzz = f; else fuzz = 1;
}

__device__ bool Metal::Scatter(const Ray& r_in, const hitRecord& rec, Vec3& attenuation, Ray& Scattered, curandState* local_rand_state) const
{
    Vec3 reflected = Reflect(UnitVector(r_in.GetDirection()), rec.normal);
    Scattered = Ray(rec.p, reflected + fuzz * RandomUnitVector(local_rand_state), r_in.GetTime());
    attenuation = albedo;
    return (Dot(Scattered.GetDirection(), rec.normal) > 0.0f);
}

__device__ Dielectric::Dielectric(float ri)
    : indexOfRefract(ri)
{
}

__device__ bool Dielectric::Scatter(const Ray& r_in, const hitRecord& rec, Vec3& attenuation, Ray& scattered, curandState* local_rand_state) const
{
    attenuation = Color(1.0f, 1.0f, 1.0f);
    float refraction_ratio = rec.front_face ? (1.0f / indexOfRefract) : indexOfRefract;

    Vec3 unit_direction = UnitVector(r_in.GetDirection());
    float cos_theta = fmin(Dot(-unit_direction, rec.normal), 1.0f);
    float sin_theta = sqrt(1.0f - cos_theta * cos_theta);

    bool cannot_refract = refraction_ratio * sin_theta > 1.0f;
    Vec3 direction;

    if (cannot_refract || Reflectance(cos_theta, refraction_ratio) > RandomDouble(local_rand_state))
        direction = Reflect(unit_direction, rec.normal);
    else
        direction = Refract(unit_direction, rec.normal, refraction_ratio);

    scattered = Ray(rec.p, direction, r_in.GetTime());
    return true;
}

__device__ float Dielectric::Reflectance(float cosine, float indexOfRefract) const
{
    float r0 = (1.0f - indexOfRefract) / (1.0f + indexOfRefract);
    r0 = r0 * r0;
    return r0 + (1.0f - r0) * pow((1.0f - cosine), 5.0f);
}
