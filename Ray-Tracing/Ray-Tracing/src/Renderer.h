#pragma once
#ifndef RENDERER_H
#define RENDERER_H

#include "vec3.h"
#include "Utils.h"
#include "vendor/stb/stb_image_write.h"

#include <vector>
#include <fstream>

class Renderer {
public:
    Renderer(int imageWidth, int imageHeight);
    ~Renderer();

	void WriteColors(Color pixel_color, int samples_per_pixel);

    void WriteOutput(int imageWidth, int imageHeight) const;

private:
    std::vector<unsigned char> m_ImageData;
};

#endif