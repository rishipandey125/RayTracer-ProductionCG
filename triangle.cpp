#include "triangle.h"
triangle::triangle() {}

triangle::triangle(point tri_vertex1, point tri_vertex2, point tri_vertex3) {
  this->vertex1 = tri_vertex1;
  this->vertex2 = tri_vertex2;
  this->vertex3 = tri_vertex3;
}

float triangle::hit(ray &casted_ray) const {

}

vec triangle::get_normal_vector(point &point_on_triangle) const {
  vec vector1 = this->vertex2-this->vertex1;
  vec vector2 = this->vertex3-this->vertex2;
  return vector1.cross(vector2);
}
