#ifndef AABB_H
#define AABB_H
#include "ray.h"
#include "vec.h"
//Header File for AABB Class
class aabb {
  public:
    //Constructors
    aabb();
    aabb(point a, point b);
    //Member Functions
    float hit(ray &casted_ray);
    aabb surrounding_box(aabb &box);
    //Member Variables
    point minimum;
    float maximum;
};

#endif
