#pragma once
#ifndef Material_H
#define Material_H

#include "Utils.h"

struct hit_record;

class Material {
    public:
        virtual bool scatter(
            const Ray& r_in, const hitRecord& rec, Color& attenuation, Ray& scattered
        ) const = 0;
};

class Lambertian : public Material {
    public:
        Lambertian(const Color& a) : albedo(a) {}

        virtual bool scatter(
            const Ray& r_in, const hitRecord& rec, Color& attenuation, Ray& scattered
        ) const override {
            auto scatter_direction = rec.normal + randomUnitVector();

            // Catch degenerate scatter direction
            if (scatter_direction.nearZero())
                scatter_direction = rec.normal;

            scattered = Ray(rec.p, scatter_direction);
            attenuation = albedo;
            return true;
        }

    public:
        Color albedo;
};

class Metal : public Material {
    public:
        Metal(const Color& a, double f) : albedo(a), fuzz(f < 1 ? f : 1) {}

        virtual bool scatter(
            const Ray& r_in, const hitRecord& rec, Color& attenuation, Ray& scattered
        ) const override {
            vec3 reflected = reflect(unitVector(r_in.GetDirection()), rec.normal);
            scattered = Ray(rec.p, reflected + fuzz * randomInUnitCube());
            attenuation = albedo;
            return (dot(scattered.GetDirection(), rec.normal) > 0);
        }

    public:
        Color albedo;
        double fuzz;
};

class Dielectric : public Material {
    public:
        Dielectric(double index_of_refraction) : ir(index_of_refraction) {}

        virtual bool scatter(
            const Ray& r_in, const hitRecord& rec, Color& attenuation, Ray& scattered
        ) const override {
            attenuation = Color(1.0, 1.0, 1.0);
            double refraction_ratio = rec.front_face ? (1.0 / ir) : ir;

            vec3 unit_direction = unitVector(r_in.GetDirection());
            double cos_theta = fmin(dot(-unit_direction, rec.normal), 1.0);
            double sin_theta = sqrt(1.0 - cos_theta * cos_theta);

            bool cannot_refract = refraction_ratio * sin_theta > 1.0;
            vec3 direction;

            if (cannot_refract || reflectance(cos_theta, refraction_ratio) > randomDouble())
                direction = reflect(unit_direction, rec.normal);
            else
                direction = refract(unit_direction, rec.normal, refraction_ratio);

            scattered = Ray(rec.p, direction);
            return true;
        }

    public:
        double ir; // Index of Refraction

    private:
        static double reflectance(double cosine, double ref_idx) {
            // Use Schlick's approximation for reflectance.
            auto r0 = (1 - ref_idx) / (1 + ref_idx);
            r0 = r0 * r0;
            return r0 + (1 - r0) * pow((1 - cosine), 5);
        }
};

#endif