#pragma once
#ifndef RENDERER_H
#define RENDERER_H

#include "vendor/stb/stb_image_write.h"

#include <vector>
#include <fstream>

class Renderer {
public:
    Renderer(int imageWidth, int imageHeight);
    ~Renderer();

    void Renderer::WriteColors(int ir, int ig, int ib);

    void WriteOutput(int imageWidth, int imageHeight) const;

private:
    std::vector<unsigned char> m_ImageData;
};

#endif