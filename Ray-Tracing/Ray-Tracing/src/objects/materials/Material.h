#pragma once
#ifndef Material_H
#define Material_H

#include "../utils/Utils.h"
#include "../objects/Hittable.h"
#include "Texture.h"

struct hitRecord;

class Material {
    public:
        virtual bool Scatter(const Ray& r_in, const hitRecord& rec, Color& attenuation, Ray& scattered) const;
        virtual Color Emitted(double u, double v, const Point3& p) const;
};

class Lambertian : public Material {
    public:
        Lambertian(const Color& a);
        Lambertian(shared_ptr<Texture> a);

        virtual bool Scatter(const Ray& r_in, const hitRecord& rec, Color& attenuation, Ray& scattered) const override;

    public:
        shared_ptr<Texture> albedo;
};

class Metal : public Material {
    public:
        Metal(const Color& a, double f) : albedo(a), fuzz(f < 1 ? f : 1) {}

        virtual bool Scatter(const Ray& r_in, const hitRecord& rec, Color& attenuation, Ray& scattered) const override;

    public:
        Color albedo;
        double fuzz;
};

class Dielectric : public Material {
    public:
        Dielectric(double index_of_refraction) : ir(index_of_refraction) {}

        virtual bool Scatter(const Ray& r_in, const hitRecord& rec, Color& attenuation, Ray& scattered) const override;

    public:
        double ir; // Index of Refraction

    private:
        static double Reflectance(double cosine, double ref_idx);
};

class DiffuseLight : public Material {
public:
    DiffuseLight(shared_ptr<Texture> a);
    DiffuseLight(Color c);

    virtual bool Scatter(const Ray& r_in, const hitRecord& rec, Color& attenuation, Ray& scattered) const override;

    virtual Color Emitted(double u, double v, const Point3& p) const override;

public:
    shared_ptr<Texture> m_Emit;
};

class Isotropic : public Material {
public:
    Isotropic(Color c);
    Isotropic(shared_ptr<Texture> a);

    virtual bool Scatter(const Ray& r_in, const hitRecord& rec, Color& attenuation, Ray& scattered) const override;

public:
    shared_ptr<Texture> albedo;
};

#endif