#ifndef CAMERA_H
#define CAMERA_H
#include "vec.h"
#include "ray.h"
//Header File for Camera Class
class camera {
  public:
    //Default Constructor
    camera();
    //Specified Constructor
    camera(point camera_origin, point camera_look_at,
          float camera_focal_length, float camera_aspect_ratio,
          float camera_viewport_height);
    //Cast Perspective Ray Function
    ray cast_perspective_ray(float &u, float &v);
    //Cast Orthogonal Ray Function
    ray cast_orthogonal_ray(float &u, float &v);
    //Camera Parameters
    point origin;
    point look_at;
    float focal_length;
    float aspect_ratio;
    float viewport_height;
    //Calculated Ray Helper Vectors
    float viewport_width;
    point lower_left_corner;
    vec horizontal;
    vec vertical;
    vec w;

};

#endif
