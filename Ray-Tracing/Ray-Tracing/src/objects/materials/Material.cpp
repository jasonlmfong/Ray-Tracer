#include "Material.h"

bool Material::Scatter(const Ray& r_in, const hitRecord& rec, Color& attenuation, Ray& scattered) const
{
    return false;
}

Color Material::Emitted(double u, double v, const Point3& p) const
{
    return Color(0, 0, 0);
}

Lambertian::Lambertian(const Color& a)
    : albedo(make_shared<SolidColor>(a))
{
}

Lambertian::Lambertian(shared_ptr<Texture> a)
    : albedo(a)
{
}

bool Lambertian::Scatter(const Ray& r_in, const hitRecord& rec, Color& attenuation, Ray& scattered) const
{
    auto scatter_direction = rec.normal + RandomUnitVector();

    // Catch degenerate scatter direction
    if (scatter_direction.NearZero())
        scatter_direction = rec.normal;

    scattered = Ray(rec.p, scatter_direction, r_in.GetTime());
    attenuation = albedo->GetValue(rec.u, rec.v, rec.p);
    return true;
}

bool Metal::Scatter(const Ray& r_in, const hitRecord& rec, Color& attenuation, Ray& scattered) const
{
    Vec3 reflected = reflect(UnitVector(r_in.GetDirection()), rec.normal);
    scattered = Ray(rec.p, reflected + fuzz * RandomUnitVector(), r_in.GetTime());
    attenuation = albedo;
    return (Dot(scattered.GetDirection(), rec.normal) > 0);
}

bool Dielectric::Scatter(const Ray& r_in, const hitRecord& rec, Color& attenuation, Ray& scattered) const
{
    attenuation = Color(1.0, 1.0, 1.0);
    double refraction_ratio = rec.front_face ? (1.0 / ir) : ir;

    Vec3 unit_direction = UnitVector(r_in.GetDirection());
    double cos_theta = fmin(Dot(-unit_direction, rec.normal), 1.0);
    double sin_theta = sqrt(1.0 - cos_theta * cos_theta);

    bool cannot_refract = refraction_ratio * sin_theta > 1.0;
    Vec3 direction;

    if (cannot_refract || Reflectance(cos_theta, refraction_ratio) > RandomDouble())
        direction = reflect(unit_direction, rec.normal);
    else
        direction = refract(unit_direction, rec.normal, refraction_ratio);

    scattered = Ray(rec.p, direction, r_in.GetTime());
    return true;
}

double Dielectric::Reflectance(double cosine, double ref_idx)
{
    // Use Schlick's approximation for reflectance.
    auto r0 = (1 - ref_idx) / (1 + ref_idx);
    r0 = r0 * r0;
    return r0 + (1 - r0) * pow((1 - cosine), 5);
}

DiffuseLight::DiffuseLight(shared_ptr<Texture> a)
    : m_Emit(a)
{
}

DiffuseLight::DiffuseLight(Color c)
    : m_Emit(make_shared<SolidColor>(c))
{
}

bool DiffuseLight::Scatter(const Ray& r_in, const hitRecord& rec, Color& attenuation, Ray& scattered) const
{
    return false;
}

Color DiffuseLight::Emitted(double u, double v, const Point3& p) const
{
    return m_Emit->GetValue(u, v, p);
}

Isotropic::Isotropic(Color c)
    : albedo(make_shared<SolidColor>(c))
{
}

Isotropic::Isotropic(shared_ptr<Texture> a)
    : albedo(a) 
{
}

bool Isotropic::Scatter(const Ray& r_in, const hitRecord& rec, Color& attenuation, Ray& scattered) const
{
    scattered = Ray(rec.p, RandomUnitVector(), r_in.GetTime());
    attenuation = albedo->GetValue(rec.u, rec.v, rec.p);
    return true;
}
