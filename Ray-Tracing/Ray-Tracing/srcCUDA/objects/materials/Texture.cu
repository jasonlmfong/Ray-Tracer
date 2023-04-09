#include "Texture.h"

__device__ SolidColor::SolidColor()
{
}

__device__ SolidColor::SolidColor(Color c)
    : colorValue(c)
{
}

__device__ SolidColor::SolidColor(float red, float green, float blue)
    : SolidColor(Color(red, green, blue))
{
}

__device__ Color SolidColor::GetValue(float u, float v, const Vec3& p) const
{
    return colorValue;
}

__device__ CheckerTexture::CheckerTexture()
{
}

__device__ CheckerTexture::CheckerTexture(Texture* _even, Texture* _odd)
    : even(_even), odd(_odd)
{
}

__device__ CheckerTexture::CheckerTexture(Color c1, Color c2)
    : even(&SolidColor(c1)), odd(&SolidColor(c2))
{
}

__device__ Color CheckerTexture::GetValue(float u, float v, const Point3& p) const
{
    auto sines = sin(10 * p.x()) * sin(10 * p.y()) * sin(10 * p.z());
    if (sines < 0)
        return odd->GetValue(u, v, p);
    else
        return even->GetValue(u, v, p);
}

//__device__ NoiseTexture::NoiseTexture()
//{
//}
//
//__device__ Color NoiseTexture::GetValue(float u, float v, const Point3& p) const
//{
//    return Color(1, 1, 1) * m_Noise.Noise(p);
//}
//
//__device__ SmoothNoiseTexture::SmoothNoiseTexture()
//{
//}
//
//__device__ SmoothNoiseTexture::SmoothNoiseTexture(float sc)
//    : m_Scale(sc)
//{
//}
//
//__device__ Color SmoothNoiseTexture::GetValue(float u, float v, const Point3& p) const
//{
//    return Color(1, 1, 1) * 0.5 * (1 + sin(m_Scale * p.z() + 10 * m_Noise.Turbulence(p)));
//}
//
//__device__ ImageTexture::ImageTexture()
//    : m_Data(nullptr), m_Width(0), m_Height(0), bytesPerScanline(0)
//{
//}

//__device__ ImageTexture::ImageTexture(const char* filename)
//{
//    auto components_per_pixel = bytesPerPixel;
//
//    m_Data = stbi_load(
//        filename, &m_Width, &m_Height, &components_per_pixel, components_per_pixel);
//
//    if (!m_Data) {
//        std::cerr << "ERROR: Could not load texture image file '" << filename << "'.\n";
//        m_Width = m_Height = 0;
//    }
//
//    bytesPerScanline = bytesPerPixel * m_Width;
//}
//
//__device__ ImageTexture::~ImageTexture()
//{
//    delete m_Data;
//}
//
//__device__ Color ImageTexture::GetValue(float u, float v, const Vec3& p) const
//{
//    // If we have no texture data, then return solid cyan as a debugging aid.
//    if (m_Data == nullptr)
//        return Color(0, 1, 1);
//
//    // Clamp input texture coordinates to [0,1] x [1,0]
//    u = clamp(u, 0.0, 1.0);
//    v = 1.0 - clamp(v, 0.0, 1.0);  // Flip V to image coordinates
//
//    auto i = static_cast<int>(u * m_Width);
//    auto j = static_cast<int>(v * m_Height);
//
//    // Clamp integer mapping, since actual coordinates should be less than 1.0
//    if (i >= m_Width)  i = m_Width - 1;
//    if (j >= m_Height) j = m_Height - 1;
//
//    const auto color_scale = 1.0 / 255.0;
//    auto pixel = m_Data + j * bytesPerScanline + i * bytesPerPixel; // pointer arithmetic
//
//    return Color(color_scale * pixel[0], color_scale * pixel[1], color_scale * pixel[2]);
//}
