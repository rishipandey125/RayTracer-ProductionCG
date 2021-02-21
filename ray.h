#ifndef RAY_H
#define RAY_H
#include "vec.h"
//Header File for Ray Class
class ray {
  public:
    //Constructors
    ray();
    ray(const point &ray_origin, vec &ray_direction);
    //Get Point at Function
    point get_point_at(float t);
    //Member Variables
    point origin;
    vec direction;
};

#endif
