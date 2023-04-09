#pragma once
#ifndef CAMERA_H
#define CAMERA_H

#include "utils/Ray.h"
#include "utils/Utils.h"

class Camera {
public:
    __device__ Camera(Point3 lookfrom, Point3 lookat, Vec3 vup, float vfov, float aspect, float aperture, float focus_dis, float _time0, float _time1);

    __device__ Ray GetRay(float s, float t, curandState* local_rand_state);

private:
    Point3 origin;
    Point3 lower_left_corner;
    Vec3 horizontal;
    Vec3 vertical;
    Vec3 u, v, w;
    float lens_radius;
    float time0, time1; // shutter open/close times
};

#endif
