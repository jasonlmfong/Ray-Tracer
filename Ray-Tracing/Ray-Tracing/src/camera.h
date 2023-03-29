#pragma once
#ifndef CAMERA_H
#define CAMERA_H

#include "Utils.h"

class Camera {
public:
    Camera(Point3 lookfrom,
        Point3 lookat,
        vec3   vup,
        double vfov, // vertical field-of-view in degrees
        double aspect_ratio,
        double aperture,
        double focus_dist,
        double _time0,
        double _time1
    );

    Ray getRay(double s, double t) const;

private:
    Point3 origin;
    Point3 lower_left_corner;
    vec3 horizontal;
    vec3 vertical;
    vec3 u, v, w;
    double lens_radius;
    double time0, time1; // shutter open/close times
};
#endif