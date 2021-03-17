#include "triangle.h"
//Triangle Class

//Default Constructor
triangle::triangle() {}

/*
Specific Constructor:
@param tri_vertex1, tri_vertex2, tri_vertex3: vertices of triangle
@param geo_base_color: base color of triangle
*/
triangle::triangle(point tri_vertex1, point tri_vertex2, point tri_vertex3, color geo_base_color) {
  this->vertex1 = tri_vertex1;
  this->vertex2 = tri_vertex2;
  this->vertex3 = tri_vertex3;
  this->edge1 = this->vertex2-this->vertex1;
  this->edge2 = this->vertex3-this->vertex1;
  this->normal_vector = ((this->edge1).cross(this->edge2));
  this->base_color = geo_base_color;
}

/*
Hit Function for Triangle:
@param casted_ray: ray casted at geometry
@return: -1 for no hit, and t (parametric value on ray) for a hit
*/
bool triangle::hit(ray &casted_ray, double t_min, double t_max, hit_record &rec) const {
  float epsilon = 0.0000001;
  vec h = (casted_ray.direction).cross(this->edge2);
  float a = (this->edge1).dot(h);
  if (a > (-1*epsilon) && a < epsilon) {
    return false;
  }
  float f = 1.0/a;
  vec s = casted_ray.origin-this->vertex1;
  float u = f * s.dot(h);
  if (u < 0 || u > 1) {
    return false;
  }
  vec q = s.cross(this->edge1);
  float v = f * (casted_ray.direction).dot(q);
  if (v < 0 || (u+v) > 1) {
    return false;
  }
  float t = f * this->edge2.dot(q);
  if (t > epsilon) {
    if (t < t_min || t > t_max) {
      return false;
    }
    rec.t = t;
    rec.hit_point = casted_ray.get_point_at(t);
    rec.normal = this->get_normal_vector(rec.hit_point);
    rec.base_color = this->get_base_color();
    return true;
  }
  return false;
}

/*
Getting the Normal Vector of the Triangle
@return: normal vector
*/
vec triangle::get_normal_vector(point &point_on_triangle) const {
  return this->normal_vector;
}

//returns the base color of the triangle
color triangle::get_base_color() const {
  return this->base_color;
}

aabb triangle::bounding_box() const {
  vec temp = vec();
  return aabb(temp,temp);
}
