#ifndef CAMERA_H
#define CAMERA_H
#include "vec.h"
#include "ray.h"
class camera {
  public:
    camera();
    camera(point &camera_origin, point &camera_look_at, float &camera_focal_length, float &camera_aspect_ratio, float &camera_viewport_height);
    ray cast_perspective_ray(float &u, float &v);
    ray cast_orthogonal_ray(float &u, float &v);
    point origin;
    point look_at;
    float focal_length;
    float aspect_ratio;
    float viewport_height;
    float viweport_width;
    point lower_left_corner;
    vec horizontal;
    vec vertical;

};

#endif
