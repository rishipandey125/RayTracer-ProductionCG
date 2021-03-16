#ifndef SPHERE_H
#define SPHERE_H
#include "geometry.h"
#include "ray.h"
#include "vec.h"
#include "aabb.h"
//Header File for Sphere Class
class sphere : public geometry {
  public:
    //Constructors
    sphere();
    sphere(point sphere_center, float sphere_radius, color geo_base_color);
    //Geometry Functions
    float hit(ray &casted_ray) const override;
    vec get_normal_vector(point &point_on_sphere) const override;
    color get_base_color() const override;
    aabb bounding_box() const override;
    //Member Variables
    point center;
    float radius;
    color base_color;
    aabb bb;
};

#endif
