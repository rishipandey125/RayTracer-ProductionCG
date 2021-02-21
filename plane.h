#ifndef PLANE_H
#define PLANE_H
#include "geometry.h"
#include "ray.h"
#include "vec.h"
class plane : public geometry {
  public:
    plane();
    plane(point plane_vertex1, point plane_vertex2, point plane_vertex3, point plane_vertex4, color geo_base_color);
    float hit(ray &casted_ray) const override;
    vec get_normal_vector(point &point_on_plane) const override;
    point vertex1;
    point vertex2;
    point vertex3;
    point vertex4;
    vec edge1;
    vec edge2;
    vec normal_vector;
    color base_color;
};

#endif
