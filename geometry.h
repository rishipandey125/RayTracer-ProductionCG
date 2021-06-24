#ifndef GEOMETRY_H
#define GEOMETRY_H
#include "material.h"


//Geometry Parent Class: Virtual Functions Overriden by Geometry Children (Sphere,bvh_node,bvh_tree,Hittables)
class geometry {
  public:
    virtual ~geometry() = default;
    virtual bool hit(ray &casted_ray, double t_min, double t_max, hit_record &rec) const = 0;
    virtual vec get_normal_vector(point &point_on_surface) const = 0;
    virtual material * get_material() const = 0;
    virtual aabb get_bounding_box() const = 0;
    virtual geometry * get_left() const = 0;
    virtual geometry * get_right() const = 0;
    virtual bool is_leaf() const = 0;
    virtual std::vector<geometry*> get_geo() const = 0;
};

#endif
