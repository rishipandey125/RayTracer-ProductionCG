#include "triangle.h"
//Triangle Class

//Default Constructor
triangle::triangle() {}


float compute_smallest(float x, float y, float z) {
  float smallest = x;
  if (y < smallest)
    smallest = y;
  if (z < smallest)
    smallest = z;
  return smallest;
}

float compute_largest(float x, float y, float z) {
  float largest = x;
  if (y > largest)
    largest = y;
  if (z > largest)
    largest = z;
  return largest;
}
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
  vec minimum = vec(compute_smallest(tri_vertex1.x,tri_vertex2.x,tri_vertex3.x),
                    compute_smallest(tri_vertex1.y,tri_vertex2.y,tri_vertex3.y),
                    compute_smallest(tri_vertex1.z,tri_vertex2.z,tri_vertex3.z));

  vec maximum = vec(compute_largest(tri_vertex1.x,tri_vertex2.x,tri_vertex3.x),
                    compute_largest(tri_vertex1.y,tri_vertex2.y,tri_vertex3.y),
                    compute_largest(tri_vertex1.z,tri_vertex2.z,tri_vertex3.z));
  this->box = aabb(minimum,maximum);
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
  return this->box;
}
