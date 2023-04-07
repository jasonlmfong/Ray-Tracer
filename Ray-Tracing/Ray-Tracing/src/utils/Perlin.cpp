#include "Perlin.h"

Perlin::Perlin()
{
    m_RanFloat = new double[m_PointCount];
    for (int i = 0; i < m_PointCount; ++i) {
        m_RanFloat[i] = RandomDouble();
    }

    m_PermX = PerlinGeneratePerm();
    m_PermY = PerlinGeneratePerm();
    m_PermZ = PerlinGeneratePerm();
}

Perlin::~Perlin()
{
    delete[] m_RanFloat;
    delete[] m_PermX;
    delete[] m_PermY;
    delete[] m_PermZ;
}

double Perlin::Noise(const Point3& p) const
{
    auto i = static_cast<int>(4 * p.x()) & 255;
    auto j = static_cast<int>(4 * p.y()) & 255;
    auto k = static_cast<int>(4 * p.z()) & 255;

    return m_RanFloat[m_PermX[i] ^ m_PermY[j] ^ m_PermZ[k]];
}

int* Perlin::PerlinGeneratePerm()
{
    auto p = new int[m_PointCount];

    for (int i = 0; i < Perlin::m_PointCount; i++)
        p[i] = i;

    Permute(p, m_PointCount);

    return p;
}

void Perlin::Permute(int* p, int n)
{
    for (int i = n - 1; i > 0; i--) {
        int target = RandomInt(0, i);
        int tmp = p[i];
        p[i] = p[target];
        p[target] = tmp;
    }
}
