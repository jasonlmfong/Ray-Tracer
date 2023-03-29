#pragma once
#ifndef CAMERA_H
#define CAMERA_H

#include "Utils.h"

class Camera {
public:
    Camera(Point3 lookfrom,
        Point3 lookat,
        Vec3   vup,
        double vfov, // vertical field-of-view in degrees
        double aspect_ratio,
        double aperture,
        double focus_dist,
        double _time0,
        double _time1
    );

    Ray GetRay(double s, double t) const;

private:
    Point3 origin;
    Point3 lower_left_corner;
    Vec3 horizontal;
    Vec3 vertical;
    Vec3 u, v, w;
    double lens_radius;
    double time0, time1; // shutter open/close times
};
#endif