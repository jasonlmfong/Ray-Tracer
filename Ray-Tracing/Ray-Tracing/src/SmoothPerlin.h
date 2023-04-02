#pragma once
#ifndef SMOOTHPERLIN_H
#define SMOOTHPERLIN_H

#include "Utils.h"

class SmoothPerlin {
public:
    SmoothPerlin();

    ~SmoothPerlin();

    double Noise(const Point3& p) const;

private:
    static const int m_PointCount = 256;
    double* m_RanFloat;
    int* m_PermX;
    int* m_PermY;
    int* m_PermZ;

    static int* SmoothPerlinGeneratePerm();

    static void Permute(int* p, int n);

    static double TrilinearInterp(double c[2][2][2], double u, double v, double w);
};

#endif