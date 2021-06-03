#ifndef SPHERE_H
#define SPHERE_H
//Header File for Sphere Class
class sphere : public geometry {
  public:
    //Constructors
    sphere();
    sphere(point sphere_center, float sphere_radius, material *geo_material);
    //Geometry Functions
    bool hit(ray &casted_ray, double t_min, double t_max, hit_record &rec) const override;
    vec get_normal_vector(point &point_on_sphere) const override;
    material * get_material() const override;
    aabb get_bounding_box() const override;
    //Member Variables
    point center;
    float radius;
    material *geo_material;
    aabb bounding_box;
};

#endif
