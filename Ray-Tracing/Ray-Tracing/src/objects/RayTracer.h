#pragma once
#ifndef RAYTRACER_H
#define RAYTRACER_H

#include "HittableList.h"
#include "Material.h"

#include <iostream>
Color RayColor1(const Ray& r, const Hittable& world, int depth) {
    hitRecord rec;

    // If we've exceeded the ray bounce limit, no more light is gathered.
    if (depth <= 0)
        return Color(0, 0, 0);

    if (world.Hit(r, 0.001, infinity, rec)) {
        Ray scattered;
        Color attenuation;
        if (rec.mat_ptr->Scatter(r, rec, attenuation, scattered))
            return attenuation * RayColor(scattered, world, depth - 1);
        return Color(0, 0, 0);
    }
    Vec3 unit_direction = UnitVector(r.GetDirection());
    auto t = 0.5 * (unit_direction.y() + 1.0);
    return (1.0 - t) * Color(1.0, 1.0, 1.0) + t * Color(0.5, 0.7, 1.0);
}

Color RayColor2(const Ray& r, const Color& background, const Hittable& world, int depth) {
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