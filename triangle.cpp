#include "triangle.h"
triangle::triangle() {}

triangle::triangle(point tri_vertex1, point tri_vertex2, point tri_vertex3) {
  this->vertex1 = tri_vertex1;
  this->vertex2 = tri_vertex2;
  this->vertex3 = tri_vertex3;
}

float triangle::hit(ray &casted_ray) const {
  /*
  Define Epsilon: ep = 0.0000001
  Define Edge 1 an Edge 2:
  edge1 = vertex1-vertex0
  edge2 = vertex2-vertex0
  Define h vec:
    h = (casted_ray.direction).cross(edge2)
  define const a:
    a = edge1.dot(h)
  if (a > -Ep && a < Ep) (close to zero)
    then no hit! rays are parallel
  define const f:
    f = 1.0/a
  define vec s:
    s = casted_ray.origin-vertex0
  define const u:
    u = f* s.dot(h)
  if u < 0 or u > 1:
    no hit!
  q = s.cross(edge1)
  v = f * (casted_ray.direction).dot(q)
  if v < 0 || (u+v) > 1:
    no hit!
  compute t!
  t = f * edge2.dot(q)
  if t > ep:
    hit!
    return t
  return no hit for good measure
  */

}

vec triangle::get_normal_vector(point &point_on_triangle) const {
  vec vector1 = this->vertex2-this->vertex1;
  vec vector2 = this->vertex3-this->vertex2;
  return vector1.cross(vector2);
}
