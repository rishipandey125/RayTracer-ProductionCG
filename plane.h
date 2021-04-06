#ifndef PLANE_H
#define PLANE_H
#include "helpers.cpp"
//Header File for Plane Class
class plane : public geometry {
  public:
    //Default Constructor
    plane();
    //Specified Constructor
    plane(point plane_vertex1, point plane_vertex2, point plane_vertex3, point plane_vertex4, material * geo_material);
    //Geometry Functions
    bool hit(ray &casted_ray, double t_min, double t_max, hit_record &rec) const override;
    vec get_normal_vector(point &point_on_plane) const override;
    material * get_material() const override;
    aabb bounding_box() const override;
    //Plane Vertices
    point vertex1;
    point vertex2;
    point vertex3;
    point vertex4;
    //Computed Helper Vector
    vec edge1;
    vec edge2;
    vec normal_vector;
    vec min;
    vec max;
    //Plane Base Color
    material * geo_material;
    //bounding box
    aabb box;
};

#endif
