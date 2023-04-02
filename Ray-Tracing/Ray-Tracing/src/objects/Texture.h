#pragma once
#ifndef TEXTURE_H
#define TEXTURE_H

#include "../Utils.h"
#include "../Perlin.h"
#include "../SmoothPerlin.h"

class Texture {
public:
    virtual Color GetValue(double u, double v, const Point3& p) const = 0;
};

class SolidColor : public Texture {
public:
    SolidColor();
    SolidColor(Color c);

    SolidColor(double red, double green, double blue);

    virtual Color GetValue(double u, double v, const Vec3& p) const override;

private:
    Color colorValue;
};

class CheckerTexture : public Texture {
public:
    CheckerTexture();

    CheckerTexture(shared_ptr<Texture> _even, shared_ptr<Texture> _odd);

    CheckerTexture(Color c1, Color c2);

    virtual Color GetValue(double u, double v, const Point3& p) const override;

public:
    shared_ptr<Texture> odd;
    shared_ptr<Texture> even;
};

class NoiseTexture : public Texture {
public:
    NoiseTexture();

    virtual Color GetValue(double u, double v, const Point3& p) const override;

public:
    Perlin m_Noise;
};

class SmoothNoiseTexture : public Texture {
public:
    SmoothNoiseTexture();
    SmoothNoiseTexture(double sc);

    virtual Color GetValue(double u, double v, const Point3& p) const override;

public:
    SmoothPerlin m_Noise;
    double m_Scale;
};

#endif