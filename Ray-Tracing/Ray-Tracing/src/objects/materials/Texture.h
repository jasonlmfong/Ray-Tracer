#pragma once
#ifndef TEXTURE_H
#define TEXTURE_H

#include "../utils/Utils.h"
#include "../utils/Perlin.h"
#include "../utils/SmoothPerlin.h"
#include "../vendor/stb/stb_image.h"
#include "../vendor/stb/stb_image_write.h"

#include <iostream>

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

class ImageTexture : public Texture {
public:
    const static int bytesPerPixel = 3;

    ImageTexture();

    ImageTexture(const char* filename);

    ~ImageTexture();

    virtual Color GetValue(double u, double v, const Vec3& p) const override;

private:
    unsigned char* m_Data;
    int m_Width, m_Height;
    int bytesPerScanline;
};

#endif