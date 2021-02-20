#ifndef GEOMETRY_H
#define GEOMETRY_H
#include "ray.h"
class geometry {
  public:
    virtual float hit(ray &casted_ray) const = 0;
};

#endif
