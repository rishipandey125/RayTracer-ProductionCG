#ifndef BVH_NODE_H
#define BVH_NODE_H

//Header File for bvh_node Class
class bvh_node : public geometry {
  public:
    //Constructors
    bvh_node();
    //This is to create the leaf nodes
    bvh_node(std::vector <geometry*> geo, int num_geo);
    //Geometry Functions
    bool hit(ray &casted_ray, double t_min, double t_max, hit_record &rec) const override;
    vec get_normal_vector(point &point_on_sphere) const override;
    material * get_material() const override;
    aabb get_bounding_box() const override;
    geometry * get_left() const override;
    geometry * get_right() const override;
    //Member Variables
    geometry *left;
    geometry *right;
    aabb box;
};
#endif
