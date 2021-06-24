#ifndef HITTABLES_H
#define HITTABLES_H
#include <vector>

class hittables : public geometry {
  public:
    //Constructors
    hittables();
    //Destructor
    ~hittables();
    //This Builds the Hittable Lists
    hittables(geometry * object);
    hittables(std::vector<geometry*> scene_geo);
    //Geometry Functions
    bool hit(ray &casted_ray, double t_min, double t_max, hit_record &rec) const override;
    vec get_normal_vector(point &point_on_sphere) const override;
    material * get_material() const override;
    aabb get_bounding_box() const override;
    geometry * get_left() const override;
    geometry * get_right() const override;
    void add(geometry * object);
    //Member Variables
    std::vector<geometry*> geo;


};
#endif
