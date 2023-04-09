#pragma once
#ifndef RAYTRACER_H
#define RAYTRACER_H

#include "../utils/Cuda.h"
#include "objects/HittableList.h"
#include "materials/Material.h"

// Constant
const int MAX_DEPTH = 50;

__device__ Color RayColor(const Ray& r, Hittable** world, curandState* local_rand_state) 
{
    Ray curr_Ray = r;
    Color curr_attenuation = Color(1.0, 1.0, 1.0);

    for (int i = 0; i < MAX_DEPTH; i++) 
    {
        hitRecord rec;
        if ((*world)->Hit(curr_Ray, 0.001f, FLT_MAX, rec)) // replace infinity with FLT_MAX
        {
            Ray scattered;
            Color attenuation;
            if (rec.mat_ptr->Scatter(curr_Ray, rec, attenuation, scattered, local_rand_state)) 
            {
                curr_attenuation *= attenuation;
                curr_Ray = scattered;
            }
            else 
            {
                return Color(0.0, 0.0, 0.0); // background color 
            }
        }
        else 
        {
            // background lerp color
            Vec3 unit_direction = UnitVector(curr_Ray.GetDirection());
            float t = 0.5f * (unit_direction.y() + 1.0f);
            Color c = (1.0f - t) * Vec3(1.0, 1.0, 1.0) + t * Vec3(0.5, 0.7, 1.0);
            return curr_attenuation * c;
        }
    }
    return Color(0.0, 0.0, 0.0); // exceeded recursion
}

#endif