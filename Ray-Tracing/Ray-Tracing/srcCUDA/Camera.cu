#include "Camera.h"

__device__ Camera::Camera(Point3 lookfrom, Point3 lookat, Vec3 vup, float vfov, float aspect, float aperture, float focus_dist, float _time0, float _time1)
{ 
    // vfov is top to bottom in degrees
    float theta = DegreesToRadians(vfov);
    float half_height = tan(theta / 2.0f);
    float half_width = aspect * half_height;

    w = UnitVector(lookfrom - lookat);
    u = UnitVector(Cross(vup, w));
    v = Cross(w, u);

    origin = lookfrom;
    horizontal = 2.0f * half_width * focus_dist * u;
    vertical = 2.0f * half_height * focus_dist * v;
    lower_left_corner = origin - half_width * focus_dist * u - half_height * focus_dist * v - focus_dist * w;

    lens_radius = aperture / 2.0f;
    time0 = _time0;
    time1 = _time1;
}

__device__ Ray Camera::GetRay(float s, float t, curandState* local_rand_state)
{
    Vec3 rd = lens_radius * RandomInUnitDisk(local_rand_state);
    Vec3 offset = u * rd.x() + v * rd.y();
    return Ray(origin + offset, lower_left_corner + s * horizontal + t * vertical - origin - offset, RandomDoubleBetween(time0, time1, local_rand_state));
}
