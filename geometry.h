#ifndef GEOMETRY_H
#define GEOMETRY_H
#include "material.h"


//Geometry Parent Class: Virtual Functions Overriden by Geometry Children (Sphere,Plane,Triangle)
class geometry {
  public:
    virtual bool hit(ray &casted_ray, double t_min, double t_max, hit_record &rec) const = 0;
    virtual vec get_normal_vector(point &point_on_surface) const = 0;
    virtual material * get_material() const = 0;
};

#endif
