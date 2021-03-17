#ifndef HITTABLES_H
#define HITTABLES_H
#include "geometry.h"
#include "aabb.h"
#include "ray.h"
#include "vec.h"
#include <vector>

class hittables : public geometry {
  public:
    //Constructors
    hittables();
    //This Builds the Hittable Lists
    hittables(geometry * object);
    //Geometry Functions
    point get_midpoint();
    bool hit(ray &casted_ray, double t_min, double t_max, hit_record &rec) const override;
    vec get_normal_vector(point &point_on_sphere) const override;
    color get_base_color() const override;
    aabb bounding_box() const override;
    void add(geometry * object);
    //Member Variables
    std::vector<geometry*> geo;


};
#endif
