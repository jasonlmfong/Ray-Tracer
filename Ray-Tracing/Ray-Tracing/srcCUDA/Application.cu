#include <iostream>
#include <time.h>
#include <float.h>
#include <curand_kernel.h>

#include "utils/Cuda.h"
#include "utils/Vec3.h"
#include "utils/Utils.h"
#include "utils/Ray.h"

#include "objects/objects/Sphere.h"
#include "objects/objects/MovingSphere.h"
#include "objects/objects/HittableList.h"
#include "objects/materials/Material.h"
#include "objects/RayTracer.h"

#include "Camera.h"
#include "Renderer.h"

//#include "Scene.h"

__global__ void rand_init(curandState *rand_state) {
    if (threadIdx.x == 0 && blockIdx.x == 0) {
        curand_init(6211, 0, 0, rand_state);
    }
}

__global__ void BuildScene1(Hittable** d_list, Hittable** d_world, Camera** d_Camera, int image_width, int image_height, curandState* rand_state) {
    if (threadIdx.x == 0 && blockIdx.x == 0) {
        curandState local_rand_state = *rand_state;

        d_list[0] = new Sphere(Point3(0, -1000.0, -1), 1000, new Lambertian(&CheckerTexture(Color(1.0, 0.0, 1.0), Color(0.0, 0.0, 0.0))));

        int i = 1;
        for (int a = -11; a < 11; a++) {
            for (int b = -11; b < 11; b++) {
                float choose_mat = RND;
                Point3 center(a + RND, 0.2, b + RND);
                if (choose_mat < 0.8f) {
                    Point3 center2 = center + Vec3(0, 0.5f * RND, 0);
                    d_list[i++] = new MovingSphere(center, center2, 0.0f, 1.0f, 0.2f, new Lambertian(Color(RND * RND, RND * RND, RND * RND)));
                }
                else if (choose_mat < 0.95f) {
                    d_list[i++] = new Sphere(center, 0.2f, new Metal(Color(0.5f * (1.0f + RND), 0.5f * (1.0f + RND), 0.5f * (1.0f + RND)), 0.5f * RND));
                }
                else {
                    d_list[i++] = new Sphere(center, 0.2f, new Dielectric(1.5));
                }
            }
        }

        d_list[i++] = new Sphere(Point3(0, 1, 0), 1.0, new Dielectric(1.5));
        d_list[i++] = new Sphere(Point3(-4, 1, 0), 1.0, new Lambertian(Color(0.4, 0.2, 0.1)));
        d_list[i++] = new Sphere(Point3(4, 1, 0), 1.0, new Metal(Color(0.7, 0.6, 0.5), 0.0));
        
        *rand_state = local_rand_state;
        *d_world = new HittableList(d_list, 22 * 22 + 1 + 3);

        Point3 lookfrom(13, 2, 3);
        Point3 lookat(0, 0, 0);
        float dist_to_focus = (lookfrom - lookat).Length();
        float aperture = 0.1;
        *d_Camera = new Camera(lookfrom,
            lookat,
            Vec3(0, 1, 0),
            30.0,
            float(image_width) / float(image_height),
            aperture,
            dist_to_focus,
            0.0f,
            1.0f);
    }
}

__global__ void render_init(int max_x, int max_y, curandState *rand_state) {
    int i = threadIdx.x + blockIdx.x * blockDim.x;
    int j = threadIdx.y + blockIdx.y * blockDim.y;
    if ((i >= max_x) || (j >= max_y)) 
        return;
    int pixel_index = j * max_x + i;
    // Each thread gets different seed
    curand_init(6211 + pixel_index, 0, 0, &rand_state[pixel_index]);
}

__global__ void render(Color *frame_buffer, int max_x, int max_y, int samples_per_pixel, Camera **cam, Hittable **world, curandState *rand_state) {
    int i = threadIdx.x + blockIdx.x * blockDim.x;
    int j = threadIdx.y + blockIdx.y * blockDim.y;
    if ((i >= max_x) || (j >= max_y)) 
        return;
    int pixel_index = j * max_x + i;
    curandState local_rand_state = rand_state[pixel_index];
    Color color(0, 0, 0);
    for(int s = 0; s < samples_per_pixel; s++) {
        float u = float(i + curand_uniform(&local_rand_state)) / float(max_x);
        float v = float(j + curand_uniform(&local_rand_state)) / float(max_y);
        Ray r = (*cam)->GetRay(u, v, &local_rand_state);
        color += RayColor(r, world, &local_rand_state);
    }
    rand_state[pixel_index] = local_rand_state;
    color /= float(samples_per_pixel);
    color[0] = sqrt(color[0]);
    color[1] = sqrt(color[1]);
    color[2] = sqrt(color[2]);
    frame_buffer[pixel_index] = color;
}

__global__ void free_world(Hittable **d_list, Hittable **d_world, Camera **d_Camera) {
    for(int i = 0; i < 22 * 22 + 1 + 3; i++) {
        delete ((Sphere *)d_list[i])->mat_ptr;
        delete d_list[i];
    }
    delete *d_world;
    delete *d_Camera;
}

int main() {
    int deviceId;
    int numberOfSMs;

    cudaGetDevice(&deviceId);
    cudaDeviceGetAttribute(&numberOfSMs, cudaDevAttrMultiProcessorCount, deviceId);
    printf("Device ID: %d \t Number of SMs: %d\n", deviceId, numberOfSMs);

    int image_width = 400;
    int image_height = 300;
    int samples_per_pixel = 10;
    int block_width = 16;
    int block_height = 16;

    std::cout << "Rendering a " << image_width << "x" << image_height << " image with " << samples_per_pixel << " samples per pixel ";
    std::cout << "in " << block_width << "x" << block_height << " blocks.\n";

    // allocate frame buffer
    int num_pixels = image_width * image_height;
    size_t frame_buffer_size = num_pixels * sizeof(Color);
    Color* frame_buffer;
    checkCudaErrors(cudaMallocManaged((void **)&frame_buffer, frame_buffer_size));

    // allocate random states
    curandState *d_rand_state;
    checkCudaErrors(cudaMalloc((void **)&d_rand_state, num_pixels * sizeof(curandState)));
    curandState *d_rand_state2;
    checkCudaErrors(cudaMalloc((void **)&d_rand_state2, sizeof(curandState)));

    // we need that 2nd random state to be initialized for the world creation
    rand_init<<<1, 1>>>(d_rand_state2);
    checkCudaErrors(cudaGetLastError());
    checkCudaErrors(cudaDeviceSynchronize());

    // build the world of hittables & the camera
    Hittable **d_list;
    int num_Hittables = 22 * 22 + 1 + 3;
    checkCudaErrors(cudaMalloc((void **)&d_list, num_Hittables * sizeof(Hittable *)));

    Hittable **d_world;
    checkCudaErrors(cudaMalloc((void **)&d_world, sizeof(Hittable *)));
    
    Camera **d_Camera;
    checkCudaErrors(cudaMalloc((void **)&d_Camera, sizeof(Camera *)));
    
    std::cout << "Building scene \n";
    BuildScene1<<<1, 1>>>(d_list, d_world, d_Camera, image_width, image_height, d_rand_state2);
    checkCudaErrors(cudaGetLastError());
    checkCudaErrors(cudaDeviceSynchronize());

    clock_t start, stop;
    start = clock();

    // Render the frame buffer
    dim3 blocks(image_width / block_width + 1, image_height / block_height + 1);
    dim3 threads(block_width, block_height);
    render_init<<<blocks, threads>>>(image_width, image_height, d_rand_state);
    checkCudaErrors(cudaGetLastError());
    checkCudaErrors(cudaDeviceSynchronize());

    std::cout << "Rendering image to frame buffer\n";
    render<<<blocks, threads>>>(frame_buffer, image_width, image_height, samples_per_pixel, d_Camera, d_world, d_rand_state);
    checkCudaErrors(cudaGetLastError());
    checkCudaErrors(cudaDeviceSynchronize());

    // get total time
    stop = clock();
    double timer_seconds = ((double)(stop - start)) / CLOCKS_PER_SEC;
    std::cout << "took " << timer_seconds << " seconds.\n";

    // Output frame_buffer as Image
    Renderer renderer(image_width, image_height);
    for (int j = image_height - 1; j >= 0; j--) {
        for (int i = 0; i < image_width; i++) {
            size_t pixel_index = j * image_width + i;
            int ir = int(255.99*frame_buffer[pixel_index].x());
            int ig = int(255.99*frame_buffer[pixel_index].y());
            int ib = int(255.99*frame_buffer[pixel_index].z());
            renderer.WriteColors(ir, ig, ib);
        }
    }
    std::cout << "Writing output file \n";
    renderer.WriteOutput(image_width, image_height);
    std::cout << "Done.\n";

    // clean up
    checkCudaErrors(cudaDeviceSynchronize());
    free_world<<<1, 1>>>(d_list, d_world, d_Camera);
    checkCudaErrors(cudaGetLastError());

    // free memory
    checkCudaErrors(cudaFree(d_Camera));
    checkCudaErrors(cudaFree(d_world));
    checkCudaErrors(cudaFree(d_list));
    checkCudaErrors(cudaFree(d_rand_state));
    checkCudaErrors(cudaFree(d_rand_state2));
    checkCudaErrors(cudaFree(frame_buffer));

    cudaDeviceReset();
}
