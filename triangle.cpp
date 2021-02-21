#include "triangle.h"
triangle::triangle() {}

triangle::triangle(point tri_vertex1, point tri_vertex2, point tri_vertex3, color geo_base_color) {
  this->vertex1 = tri_vertex1;
  this->vertex2 = tri_vertex2;
  this->vertex3 = tri_vertex3;
  this->edge1 = this->vertex2-this->vertex1;
  this->edge2 = this->vertex3-this->vertex1;
  this->normal_vector = (this->edge1).cross(this->edge2);
  this->base_color = geo_base_color;
}

float triangle::hit(ray &casted_ray) const {
  float epsilon = 0.0000001;
  vec h = (casted_ray.direction).cross(this->edge2);
  float a = (this->edge1).dot(h);
  if (a > (-1*epsilon) && a < epsilon) {
    return -1;
  }
  float f = 1.0/a;
  vec s = casted_ray.origin-this->vertex1;
  float u = f * s.dot(h);
  if (u < 0 || u > 1) {
    return -1.0;
  }
  vec q = s.cross(this->edge1);
  float v = f * (casted_ray.direction).dot(q);
  if (v < 0 || (u+v) > 1) {
    return -1.0;
  }
  float t = f * this->edge2.dot(q);
  if (t > epsilon) {
    return t;
  }
  return -1.0;
}

vec triangle::get_normal_vector(point &point_on_triangle) const {
  // vec vector1 = this->vertex2-this->vertex1;
  // vec vector2 = this->vertex3-this->vertex2;
  return this->normal_vector;
}
