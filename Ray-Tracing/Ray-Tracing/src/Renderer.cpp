#include "Renderer.h"

Renderer::Renderer(int imageWidth, int imageHeight)
{
    m_ImageData.reserve(imageWidth * imageHeight);
}

Renderer::~Renderer()
{
}

void Renderer::WriteColors(Color pixel_color, int samples_per_pixel)
{
    auto r = pixel_color.x();
    auto g = pixel_color.y();
    auto b = pixel_color.z();

    // Divide the color by the number of samples and gamma-correct for gamma=2.0.
    auto scale = 1.0 / samples_per_pixel;
    r = sqrt(scale * r);
    g = sqrt(scale * g);
    b = sqrt(scale * b);

    // Write the translated [0,255] value of each color component.
    m_ImageData.emplace_back((unsigned char)(256 * clamp(r, 0.0, 0.999)));
    m_ImageData.emplace_back((unsigned char)(256 * clamp(g, 0.0, 0.999)));
    m_ImageData.emplace_back((unsigned char)(256 * clamp(b, 0.0, 0.999)));
}

void Renderer::WriteOutput(int imageWidth, int imageHeight) const
{
    std::ofstream outputFile;

    stbi_write_png("../gallery/next week/SampleScene.png", imageWidth, imageHeight, 3, m_ImageData.data(), imageWidth * 3);

    outputFile.close();
}
