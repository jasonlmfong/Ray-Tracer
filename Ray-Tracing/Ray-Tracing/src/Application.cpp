#include "Utils.h"
#include "objects/RayTracer.h"
#include "Scene.h"
#include "Renderer.h"

#include <iostream>

//recording time
#include <chrono>
using namespace std::chrono;

int main() {

    // Build scene
    Scene scene;
    //scene.BuildScene1(); // 3 balls with depth of field
    //scene.BuildScene2(); // book 1 cover: different materials
    //scene.BuildScene3(); // book 1 cover with moving spheres and checkered floor
    //scene.BuildScene4(); // checkered spheres
    //scene.BuildScene5(); // marble
    //scene.BuildScene6(); // earth and marble
    //scene.BuildScene7(); // earth and sun
    //scene.BuildScene8(); // earth and suns and portal
    //scene.BuildScene9(); // Cornell box
    //scene.BuildScene10(); // Cornell box with boxes
    //scene.BuildScene11(); // Cornell box with boxes with smoke
    scene.BuildScene12(); // book 2 final scene with all features

    // Image
    const int image_width = 1000;
    const int image_height = static_cast<int>(image_width / scene.m_AspectRatio);
    const int samples_per_pixel = 500;
    const int max_depth = 50;

    // Recording the timestamp at the start of the code
    auto begin = high_resolution_clock::now();

    // Render
    Renderer renderer(image_width, image_height);

    std::cout << "image width: " << image_width << "\n" << "image height: " << image_height << std::endl;

    for (int j = image_height - 1; j >= 0; --j) 
    {
        std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
        for (int i = 0; i < image_width; ++i) 
        {
            Color pixelColor(0, 0, 0);
            for (int s = 0; s < samples_per_pixel; ++s) 
            {
                auto u = (i + RandomDouble()) / (image_width - 1);
                auto v = (j + RandomDouble()) / (image_height - 1);

                Ray r = scene.m_Camera.GetRay(u, v);
                pixelColor += RayColor(r, scene.m_Background, scene.m_World, max_depth);
            }
            renderer.WriteColors(pixelColor, samples_per_pixel);
        }
    }
    std::cout << "\nWriting output file \n";
    renderer.WriteOutput(image_width, image_height);

    // Taking a timestamp after the code is ran
    auto end = high_resolution_clock::now();

    auto duration = duration_cast<microseconds>(end - begin);

    // Displaying the elapsed time
    std::cout << "Elapsed Time: " << duration.count() << " microseconds\n";

    std::cerr << "Done.\n";

    return 0;
}