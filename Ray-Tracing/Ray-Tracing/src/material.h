#pragma once
#ifndef Material_H
#define Material_H

#include "Utils.h"
#include "Hittable.h"

struct hit_record;

class Material {
    public:
        virtual bool scatter(
            const Ray& r_in, const hitRecord& rec, Color& attenuation, Ray& scattered) const = 0;
};

class Lambertian : public Material {
    public:
        Lambertian(const Color& a) : albedo(a) {}

        virtual bool scatter(
            const Ray& r_in, const hitRecord& rec, Color& attenuation, Ray& scattered) const override;

    public:
        Color albedo;
};

class Metal : public Material {
    public:
        Metal(const Color& a, double f) : albedo(a), fuzz(f < 1 ? f : 1) {}

        virtual bool scatter(
            const Ray& r_in, const hitRecord& rec, Color& attenuation, Ray& scattered) const override;

    public:
        Color albedo;
        double fuzz;
};

class Dielectric : public Material {
    public:
        Dielectric(double index_of_refraction) : ir(index_of_refraction) {}

        virtual bool scatter(
            const Ray& r_in, const hitRecord& rec, Color& attenuation, Ray& scattered) const override;

    public:
        double ir; // Index of Refraction

    private:
        static double reflectance(double cosine, double ref_idx);
};

#endif