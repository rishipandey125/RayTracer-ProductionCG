#ifndef BVH_TREE_H
#define BVH_TREE_H

//Header File for bvh_node Class
class bvh_tree : public geometry {
  public:
    //Constructors
    bvh_tree();
    //This is to create the leaf nodes
    bvh_tree(std::vector <geometry*> geo, int num_geo);
    //destructor for deleting tree
    ~bvh_tree();
    void destroy_bvh_tree(geometry *node);
    //Geometry Functions
    bool hit(ray &casted_ray, double t_min, double t_max, hit_record &rec) const override;
    vec get_normal_vector(point &point_on_sphere) const override;
    material * get_material() const override;
    aabb get_bounding_box() const override;
    geometry * get_left() const override;
    geometry * get_right() const override;
    bool is_leaf() const override;
    std::vector<geometry*> get_geo() const override;
    //Member Variables
    geometry *head;
};
#endif
