#pragma once
#ifndef RAYTRACER_H
#define RAYTRACER_H

#include "HittableList.h"
#include "Material.h"

#include <iostream>
Color RayColor(const Ray& r, const Color& background, const Hittable& world, int depth) {
    hitRecord rec;

    // If we've exceeded the ray bounce limit, no more light is gathered.
    if (depth <= 0)
        return Color(0, 0, 0);

    // If the ray hits nothing, return the background color.
    if (!world.Hit(r, 0.001, infinity, rec))
        return background;

    Ray scattered;
    Color attenuation;
    Color emitted = rec.mat_ptr->Emitted(rec.u, rec.v, rec.p);

    if (!rec.mat_ptr->Scatter(r, rec, attenuation, scattered))
        return emitted;

    return emitted + attenuation * RayColor(scattered, background, world, depth - 1);
}

#endif