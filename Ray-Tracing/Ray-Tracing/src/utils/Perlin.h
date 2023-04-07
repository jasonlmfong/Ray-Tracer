#pragma once
#ifndef PERLIN_H
#define PERLIN_H

#include "Utils.h"

class Perlin {
public:
    Perlin();

    ~Perlin();

    double Noise(const Point3& p) const;

private:
    static const int m_PointCount = 256;
    double* m_RanFloat;
    int* m_PermX;
    int* m_PermY;
    int* m_PermZ;

    static int* PerlinGeneratePerm();

    static void Permute(int* p, int n);
};

#endif