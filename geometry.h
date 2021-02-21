#ifndef GEOMETRY_H
#define GEOMETRY_H
#include "vec.h"
#include "ray.h"
//Geometry Parent Class: Virtual Functions Overriden by Geometry Children (Sphere,Plane,Triangle)
class geometry {
  public:
    virtual float hit(ray &casted_ray) const = 0;
    virtual vec get_normal_vector(point &point_on_surface) const = 0;
    virtual color get_base_color() const = 0;
};

#endif
