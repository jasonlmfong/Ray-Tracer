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
