#include "Renderer.h"

Renderer::Renderer(int imageWidth, int imageHeight)
{
    m_ImageData.reserve(imageWidth * imageHeight);
}

Renderer::~Renderer()
{
}

void Renderer::WriteColors(int ir, int ig, int ib)
{
    // Write each color component to image data.
    m_ImageData.emplace_back((unsigned char)(ir));
    m_ImageData.emplace_back((unsigned char)(ig));
    m_ImageData.emplace_back((unsigned char)(ib));
}

void Renderer::WriteOutput(int imageWidth, int imageHeight) const
{
    std::ofstream outputFile;

    stbi_write_png("../gallery/SampleScene.png", imageWidth, imageHeight, 3, m_ImageData.data(), imageWidth * 3);

    outputFile.close();
}
