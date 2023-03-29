#include "Utils.h"

#include "Camera.h"
#include "HittableList.h"
#include "Sphere.h"
#include "Material.h"
#include "Scene.h"
#include "RayTracer.h"
#include "Renderer.h"

#include <iostream>

int main() {

    // Image
    const auto aspect_ratio = 16.0 / 9.0;
    const int image_width = 200;
    const int image_height = static_cast<int>(image_width / aspect_ratio);
    const int samples_per_pixel = 100;
    const int max_depth = 50;

    // Build scene
    Scene scene;
    scene.BuildScene1();
    //scene.BuildScene2();

    // Render

    Renderer renderer(image_width, image_height);

    std::cout << "image width: " << image_width << "\n" << "image height: " << image_height << std::endl;

    for (int j = image_height - 1; j >= 0; --j) {
        std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
        for (int i = 0; i < image_width; ++i) {
            Color pixelColor(0, 0, 0);
            for (int s = 0; s < samples_per_pixel; ++s) {
                auto u = (i + randomDouble()) / (image_width - 1);
                auto v = (j + randomDouble()) / (image_height - 1);

                Ray r = scene.m_Camera.getRay(u, v);
                pixelColor += RayColor(r, scene.m_World, max_depth);
            }
            renderer.WriteColors(pixelColor, samples_per_pixel);
        }
    }
    renderer.WriteOutput(image_width, image_height);

    std::cerr << "\nDone.\n";

    return 0;
}