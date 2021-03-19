#ifndef TRIANGLE_H
#define triangle_H
#include "geometry.h"
#include "aabb.h"
#include "ray.h"
#include "vec.h"
//Header File for Triangle Class
class triangle : public geometry {
  public:
    //Constructors
    triangle();
    triangle(point tri_vertex1, point tri_vertex2, point tri_vertex3,
      vec tri_vert_n1, vec tri_vert_n2, vec tri_vert_n3, color geo_base_color);
    //Geometry Functions
    bool hit(ray &casted_ray, double t_min, double t_max, hit_record &rec) const override;
    vec get_normal_vector(point &hit_point) const override;
    color get_base_color() const override;
    aabb bounding_box() const override;
    //Verticies
    point vertex1;
    point vertex2;
    point vertex3;
    vec vertex1_norm;
    vec vertex2_norm;
    vec vertex3_norm;
    //Computed Vectors
    vec edge1;
    vec edge2;
    vec normal_vector;
    color base_color;
    aabb box;
};

#endif
