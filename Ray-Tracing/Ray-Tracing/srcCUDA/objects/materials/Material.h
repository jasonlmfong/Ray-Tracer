#pragma once
#ifndef Material_H
#define Material_H

#include "../objects/Hittable.h"
#include "../../utils/Ray.h"
#include "../../utils/Utils.h"
#include "Texture.h"

struct hitRecord;

class Material  
{
public:
    __device__ virtual bool Scatter(const Ray& r_in, const hitRecord& rec, Color& attenuation, Ray& Scattered, curandState *local_rand_state) const;
};

class Lambertian : public Material {
public:
    __device__ Lambertian(const Color& a);
    __device__ Lambertian(Texture* a);

    __device__ virtual bool Scatter(const Ray& r_in, const hitRecord& rec, Color& attenuation, Ray& Scattered, curandState* local_rand_state) const;
    
public:
    Texture* albedo;
};

class Metal : public Material {
public:
    __device__ Metal(const Color& a, float f);
    
    __device__ virtual bool Scatter(const Ray& r_in, const hitRecord& rec, Color& attenuation, Ray& Scattered, curandState* local_rand_state) const;
    
public:
    Color albedo;
    float fuzz;
};

class Dielectric : public Material {
public:
    __device__ Dielectric(float ri);
    
    __device__ virtual bool Scatter(const Ray& r_in, const hitRecord& rec, Color& attenuation, Ray& Scattered, curandState* local_rand_state) const;

public:
    float indexOfRefract;

private:
    __device__ float Reflectance(float cosine, float ref_idx) const;
};

#endif