#include "plane.h"
plane::plane() {}

plane::plane(point plane_vertex1, point plane_vertex2, point plane_vertex3, point plane_vertex4, color geo_base_color) {
  this->vertex1 = plane_vertex1;
  this->vertex2 = plane_vertex2;
  this->vertex3 = plane_vertex3;
  this->vertex4 = plane_vertex4;
  this->edge1 = this->vertex2-this->vertex1;
  this->edge2 = this->vertex3-this->vertex1;
  this->normal_vector = ((this->edge1).cross(this->edge2));
  this->base_color = geo_base_color;
}

float plane::hit(ray &casted_ray) const {
  vec n = this->normal_vector;
  point ao = this->vertex1-casted_ray.origin;
  float denom = casted_ray.direction.dot(n);
  float t = (ao.dot(n))/denom;
  if (t > 0.0) {
    return t;
  }
  return -1.0;
}

vec plane::get_normal_vector(point &point_on_plane) const {
  return (this->normal_vector);
}

color plane::get_base_color() const {
  return this->base_color;
}
