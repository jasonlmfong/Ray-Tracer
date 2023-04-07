#include "Texture.h"

SolidColor::SolidColor()
{
}

SolidColor::SolidColor(Color c)
	: colorValue(c)
{
}

SolidColor::SolidColor(double red, double green, double blue)
	: SolidColor(Color(red, green, blue))
{
}

Color SolidColor::GetValue(double u, double v, const Vec3& p) const
{
	return colorValue;
}

CheckerTexture::CheckerTexture()
{
}

CheckerTexture::CheckerTexture(shared_ptr<Texture> _even, shared_ptr<Texture> _odd)
	: even(_even), odd(_odd)
{
}

CheckerTexture::CheckerTexture(Color c1, Color c2)
	: even(make_shared<SolidColor>(c1)), odd(make_shared<SolidColor>(c2)) 
{
}

Color CheckerTexture::GetValue(double u, double v, const Point3& p) const
{
    auto sines = sin(10 * p.x()) * sin(10 * p.y()) * sin(10 * p.z());
    if (sines < 0)
        return odd->GetValue(u, v, p);
    else
        return even->GetValue(u, v, p);
}

NoiseTexture::NoiseTexture()
{
}

Color NoiseTexture::GetValue(double u, double v, const Point3& p) const
{
    return Color(1, 1, 1) * m_Noise.Noise(p);
}

SmoothNoiseTexture::SmoothNoiseTexture()
{
}

SmoothNoiseTexture::SmoothNoiseTexture(double sc)
    : m_Scale(sc) 
{
}

Color SmoothNoiseTexture::GetValue(double u, double v, const Point3& p) const
{
    return Color(1, 1, 1) * 0.5 * (1 + sin(m_Scale * p.z() + 10 * m_Noise.Turbulence(p)));
}

ImageTexture::ImageTexture()
    : m_Data(nullptr), m_Width(0), m_Height(0), bytesPerScanline(0)
{
}

ImageTexture::ImageTexture(const char* filename)
{
    auto components_per_pixel = bytesPerPixel;

    m_Data = stbi_load(
        filename, &m_Width, &m_Height, &components_per_pixel, components_per_pixel);

    if (!m_Data) {
        std::cerr << "ERROR: Could not load texture image file '" << filename << "'.\n";
        m_Width = m_Height = 0;
    }

    bytesPerScanline = bytesPerPixel * m_Width;
}

ImageTexture::~ImageTexture()
{
    delete m_Data;
}

Color ImageTexture::GetValue(double u, double v, const Vec3& p) const
{
    // If we have no texture data, then return solid cyan as a debugging aid.
    if (m_Data == nullptr)
        return Color(0, 1, 1);

    // Clamp input texture coordinates to [0,1] x [1,0]
    u = clamp(u, 0.0, 1.0);
    v = 1.0 - clamp(v, 0.0, 1.0);  // Flip V to image coordinates

    auto i = static_cast<int>(u * m_Width);
    auto j = static_cast<int>(v * m_Height);

    // Clamp integer mapping, since actual coordinates should be less than 1.0
    if (i >= m_Width)  i = m_Width - 1;
    if (j >= m_Height) j = m_Height - 1;

    const auto color_scale = 1.0 / 255.0;
    auto pixel = m_Data + j * bytesPerScanline + i * bytesPerPixel; // pointer arithmetic

    return Color(color_scale * pixel[0], color_scale * pixel[1], color_scale * pixel[2]);
}
