#ifndef BVH_H
#define BVH_H
#include "geometry.h"
#include "hittables.h"
#include "aabb.h"
#include "ray.h"
#include "vec.h"
#include "random.cpp"
#include <vector>

class bvh : public geometry {
  public:
    //Constructors
    bvh();
    //This is to create the leaf nodes
    // bvh(hittables  &list);
    bvh(std::vector <geometry*> geo, int num_geo);
    //Geometry Functions
    bool hit(ray &casted_ray, double t_min, double t_max, hit_record &rec) const override;
    vec get_normal_vector(point &point_on_sphere) const override;
    color get_base_color() const override;
    aabb bounding_box() const override;
    //Member Variables
    geometry *left;
    geometry *right;
    aabb box;
};
#endif
