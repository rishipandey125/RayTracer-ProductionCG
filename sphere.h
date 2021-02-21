#ifndef SPHERE_H
#define SPHERE_H
#include "geometry.h"
#include "ray.h"
#include "vec.h"
class sphere : public geometry {
  public:
    sphere();
    sphere(point sphere_center, float sphere_radius);
    float hit(ray &casted_ray) const override;
    vec get_normal_vector(point &point_on_sphere) const override;
    point center;
    float radius;

};

#endif
