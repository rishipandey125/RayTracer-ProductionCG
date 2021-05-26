#ifndef BOX_H
#define BOX_H

//Header File for Plane Class
class box : public geometry {
  public:
    //Default Constructor
    box();
    //Specified Constructor
    box(point min, point max, material * geo_material);
    //Geometry Functions
    bool hit(ray &casted_ray, double t_min, double t_max, hit_record &rec) const override;
    vec get_normal_vector(point &point_on_plane) const override;
    material * get_material() const override;
    aabb bounding_box() const override;
    //Box Min Max Points
    point min_point;
    point max_point;
    //List of Sides
    std::vector<geometry*> sides;
    //Box Material
    material * geo_material;
    //bounding box
    aabb bb;
};

#endif
