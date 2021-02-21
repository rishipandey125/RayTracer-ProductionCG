#ifndef TRIANGLE_H
#define triangle_H
#include "geometry.h"
#include "ray.h"
#include "vec.h"
class triangle : public geometry {
  public:
    triangle();
    triangle(point tri_vertex1, point tri_vertex2, point tri_vertex3, color geo_base_color);
    float hit(ray &casted_ray) const override;
    vec get_normal_vector(point &point_on_triangle) const override;
    point vertex1;
    point vertex2;
    point vertex3;
    vec edge1;
    vec edge2;
    vec normal_vector;
    color base_color;
};

#endif
