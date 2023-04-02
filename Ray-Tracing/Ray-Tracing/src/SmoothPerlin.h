#pragma once
#ifndef SMOOTHPERLIN_H
#define SMOOTHPERLIN_H

#include "Utils.h"

class SmoothPerlin {
public:
    SmoothPerlin();

    ~SmoothPerlin();

    double Noise(const Point3& p) const;

    double Turbulence(const Point3& p, int depth = 7) const;

private:
    static const int m_PointCount = 256;
    Vec3* m_RanVec;
    int* m_PermX;
    int* m_PermY;
    int* m_PermZ;

    static int* SmoothPerlinGeneratePerm();

    static void Permute(int* p, int n);

    static double PerlinInterp(Vec3 c[2][2][2], double u, double v, double w);
};

#endif