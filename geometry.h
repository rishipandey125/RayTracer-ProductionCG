#ifndef GEOMETRY_H
#define GEOMETRY_H
#include "vec.h"
#include "ray.h"
#include "aabb.h"

//Hit Record for Hiting an Object
struct hit_record {
  point hit_point;
  vec normal;
  float t;
  color base_color;
};
//Geometry Parent Class: Virtual Functions Overriden by Geometry Children (Sphere,Plane,Triangle)
class geometry {
  public:
    virtual bool hit(ray &casted_ray, double t_min, double t_max, hit_record &rec) const = 0;
    virtual vec get_normal_vector(point &point_on_surface) const = 0;
    virtual color get_base_color() const = 0;
    virtual aabb bounding_box() const = 0;
};

#endif
