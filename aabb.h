#ifndef AABB_H
#define AABB_H
#include "geometry.h"
#include "ray.h"
#include "vec.h"
//Header File for AABB Class
class aabb : public geometry {
  public:
    //Constructors
    aabb();
    aabb(point a, point b);
    //Geometry Functions
    float hit(ray &casted_ray) const override;
    vec get_normal_vector(point &point_on_sphere) const override;
    color get_base_color() const override;
    //Member Functions
    point minimum;
    float maximum;
    color base_color;
};

#endif
