#ifndef PLANE_H
#define PLANE_H
#include "geometry.h"
#include "ray.h"
#include "vec.h"
//Header File for Plane Class
class plane : public geometry {
  public:
    //Default Constructor
    plane();
    //Specified Constructor
    plane(point plane_vertex1, point plane_vertex2, point plane_vertex3, point plane_vertex4, color geo_base_color);
    //Geometry Functions
    float hit(ray &casted_ray) const override;
    vec get_normal_vector(point &point_on_plane) const override;
    color get_base_color() const override;
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
    //Plane Base Color
    color base_color;
};

#endif
