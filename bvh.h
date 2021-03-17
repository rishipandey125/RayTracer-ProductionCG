#ifndef BVH_H
#define BVH_H
#include "geometry.h"
#include "aabb.h"
#include "ray.h"
#include "vec.h"
#include "random.cpp"
#include <vector>

class bvh : public geometry {
  public:
    //Constructors
    bvh();
    //This Builds the Tree
    bvh(std::vector<geometry*> scene_geometry, int num_geo);
    //Geometry Functions
    float hit(ray &casted_ray) const override;
    vec get_normal_vector(point &point_on_sphere) const override;
    color get_base_color() const override;
    aabb bounding_box() const override;
    //Member Variables
    bvh *left;
    bvh *right;
    std::vector<geometry*> *leaf_geometry;
    aabb box;
    bool leaf;

};
#endif
