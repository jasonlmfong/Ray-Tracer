#include "SmoothPerlin.h"

SmoothPerlin::SmoothPerlin()
{
    m_RanFloat = new double[m_PointCount];
    for (int i = 0; i < m_PointCount; ++i) {
        m_RanFloat[i] = RandomDouble();
    }

    m_PermX = SmoothPerlinGeneratePerm();
    m_PermY = SmoothPerlinGeneratePerm();
    m_PermZ = SmoothPerlinGeneratePerm();
}

SmoothPerlin::~SmoothPerlin()
{
    delete[] m_RanFloat;
    delete[] m_PermX;
    delete[] m_PermY;
    delete[] m_PermZ;
}

double SmoothPerlin::Noise(const Point3& p) const
{
    auto u = p.x() - floor(p.x());
    auto v = p.y() - floor(p.y());
    auto w = p.z() - floor(p.z());

    u = u * u * (3 - 2 * u);
    v = v * v * (3 - 2 * v);
    w = w * w * (3 - 2 * w);

    auto i = static_cast<int>(floor(p.x()));
    auto j = static_cast<int>(floor(p.y()));
    auto k = static_cast<int>(floor(p.z()));
    double c[2][2][2];

    for (int di = 0; di < 2; di++)
        for (int dj = 0; dj < 2; dj++)
            for (int dk = 0; dk < 2; dk++)
                c[di][dj][dk] = m_RanFloat[
                        m_PermX[(i + di) & 255] ^
                        m_PermY[(j + dj) & 255] ^
                        m_PermZ[(k + dk) & 255]
                ];

    return TrilinearInterp(c, u, v, w);
}

int* SmoothPerlin::SmoothPerlinGeneratePerm()
{
    auto p = new int[m_PointCount];

    for (int i = 0; i < SmoothPerlin::m_PointCount; i++)
        p[i] = i;

    Permute(p, m_PointCount);

    return p;
}

void SmoothPerlin::Permute(int* p, int n)
{
    for (int i = n - 1; i > 0; i--) {
        int target = RandomInt(0, i);
        int tmp = p[i];
        p[i] = p[target];
        p[target] = tmp;
    }
}

double SmoothPerlin::TrilinearInterp(double c[2][2][2], double u, double v, double w)
{
    auto accum = 0.0;
    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 2; j++)
            for (int k = 0; k < 2; k++)
                accum += (i * u + (1 - i) * (1 - u)) *
                (j * v + (1 - j) * (1 - v)) *
                (k * w + (1 - k) * (1 - w)) * c[i][j][k];

    return accum;
}
