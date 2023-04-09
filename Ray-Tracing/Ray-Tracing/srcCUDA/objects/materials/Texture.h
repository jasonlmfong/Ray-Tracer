#pragma once
#ifndef TEXTURE_H
#define TEXTURE_H

#include "../../utils/Utils.h"
//#include "../../utils/Perlin.h"
//#include "../../utils/SmoothPerlin.h"
#include "../../vendor/stb/stb_image.h"
#include "../../vendor/stb/stb_image_write.h"

#include <iostream>

class Texture {
public:
    __device__ virtual Color GetValue(float u, float v, const Point3& p) const = 0;
};

class SolidColor : public Texture {
public:
    __device__ SolidColor();
    __device__ SolidColor(Color c);

    __device__ SolidColor(float red, float green, float blue);

    __device__ virtual Color GetValue(float u, float v, const Vec3& p) const override;

private:
    Color colorValue;
};

class CheckerTexture : public Texture {
public:
    __device__ CheckerTexture();

    __device__ CheckerTexture(Texture* _even, Texture* _odd);

    __device__ CheckerTexture(Color c1, Color c2);

    __device__ virtual Color GetValue(float u, float v, const Point3& p) const override;

public:
    Texture* odd;
    Texture* even;
};

//class NoiseTexture : public Texture {
//public:
//    __device__ NoiseTexture();
//
//    __device__ virtual Color GetValue(float u, float v, const Point3& p) const override;
//
//public:
//    Perlin m_Noise;
//};
//
//class SmoothNoiseTexture : public Texture {
//public:
//    __device__ SmoothNoiseTexture();
//    __device__ SmoothNoiseTexture(float sc);
//
//    __device__ virtual Color GetValue(float u, float v, const Point3& p) const override;
//
//public:
//    SmoothPerlin m_Noise;
//    float m_Scale;
//};
//
//class ImageTexture : public Texture {
//public:
//    const static int bytesPerPixel = 3;
//
//    __device__ ImageTexture();
//
//    __device__ ImageTexture(const char* filename);
//
//    __device__ ~ImageTexture();
//
//    __device__ virtual Color GetValue(float u, float v, const Vec3& p) const override;
//
//private:
//    unsigned char* m_Data;
//    int m_Width, m_Height;
//    int bytesPerScanline;
//};

#endif