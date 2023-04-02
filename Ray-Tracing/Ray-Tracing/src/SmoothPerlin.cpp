#include "SmoothPerlin.h"

SmoothPerlin::SmoothPerlin()
{
    m_RanVec = new Vec3[m_PointCount];
    for (int i = 0; i < m_PointCount; ++i) {
        m_RanVec[i] = UnitVector(RandomVec3(-1, 1));
    }

    m_PermX = SmoothPerlinGeneratePerm();
    m_PermY = SmoothPerlinGeneratePerm();
    m_PermZ = SmoothPerlinGeneratePerm();
}

SmoothPerlin::~SmoothPerlin()
{
    delete[] m_RanVec;
    delete[] m_PermX;
    delete[] m_PermY;
    delete[] m_PermZ;
}

double SmoothPerlin::Noise(const Point3& p) const
{
    auto u = p.x() - floor(p.x());
    auto v = p.y() - floor(p.y());
    auto w = p.z() - floor(p.z());

    auto i = static_cast<int>(floor(p.x()));
    auto j = static_cast<int>(floor(p.y()));
    auto k = static_cast<int>(floor(p.z()));
    Vec3 c[2][2][2];

    for (int di = 0; di < 2; di++)
        for (int dj = 0; dj < 2; dj++)
            for (int dk = 0; dk < 2; dk++)
                c[di][dj][dk] = m_RanVec[
                        m_PermX[(i + di) & 255] ^
                        m_PermY[(j + dj) & 255] ^
                        m_PermZ[(k + dk) & 255]
                ];

    return PerlinInterp(c, u, v, w);
}

double SmoothPerlin::Turbulence(const Point3& p, int depth) const 
{
    auto accum = 0.0;
    auto temp_p = p;
    auto weight = 1.0;

    for (int i = 0; i < depth; i++) {
        accum += weight * Noise(temp_p);
        weight *= 0.5;
        temp_p *= 2;
    }

    return fabs(accum); // absolute value function 
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

double SmoothPerlin::PerlinInterp(Vec3 c[2][2][2], double u, double v, double w)
{
    auto uu = u * u * (3 - 2 * u);
    auto vv = v * v * (3 - 2 * v);
    auto ww = w * w * (3 - 2 * w);
    auto accum = 0.0;

    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 2; j++)
            for (int k = 0; k < 2; k++) {
                Vec3 weight_v(u - i, v - j, w - k);
                accum += (i * uu + (1 - i) * (1 - uu))
                    * (j * vv + (1 - j) * (1 - vv))
                    * (k * ww + (1 - k) * (1 - ww))
                    * Dot(c[i][j][k], weight_v);
            }

    return accum;
}
