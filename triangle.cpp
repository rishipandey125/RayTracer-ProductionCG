#include "triangle.h"
//Triangle Class

//Default Constructor
triangle::triangle() {}

/*
Specific Constructor:
@param tri_vertex1, tri_vertex2, tri_vertex3: vertices of triangle
@param geo_base_color: base color of triangle
*/
triangle::triangle(point tri_vertex1, point tri_vertex2, point tri_vertex3, vec tri_vert_n1, vec tri_vert_n2, vec tri_vert_n3, material * geo_material) {
  this->vertex1 = tri_vertex1;
  this->vertex2 = tri_vertex2;
  this->vertex3 = tri_vertex3;
  this->vertex1_norm = tri_vert_n1;
  this->vertex2_norm = tri_vert_n2;
  this->vertex3_norm = tri_vert_n3;
  this->edge1 = this->vertex2-this->vertex1;
  this->edge2 = this->vertex3-this->vertex1;
  this->normal_vector = vec();
  this->geo_material = geo_material;
  vec minimum = vec(compute_smallest(tri_vertex1.x,tri_vertex2.x,tri_vertex3.x),
                    compute_smallest(tri_vertex1.y,tri_vertex2.y,tri_vertex3.y),
                    compute_smallest(tri_vertex1.z,tri_vertex2.z,tri_vertex3.z));

  vec maximum = vec(compute_largest(tri_vertex1.x,tri_vertex2.x,tri_vertex3.x),
                    compute_largest(tri_vertex1.y,tri_vertex2.y,tri_vertex3.y),
                    compute_largest(tri_vertex1.z,tri_vertex2.z,tri_vertex3.z));
  this->box = aabb(minimum,maximum);
}

/*
Triangle Hit Function
@param casted_ray: ray casted into the scene
@param t_min & t_max: max and min t values for parametric hit
@param rec: record to store a hit
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
    rec.geo_material = this->get_material();
    return true;
  }
  return false;
}

/*
Getting the Normal Vector of the Triangle
@return: normal vector
*/
vec triangle::get_normal_vector(point &hit_point) const {
  // vec v0 = this->edge1;
  // vec v1 = this->edge2;
  vec v2 = hit_point - this->vertex1;
  float d00 = this->edge1.dot(this->edge1);
  float d01 = this->edge1.dot(this->edge2);
  float d11 = this->edge2.dot(this->edge2);
  float d20 = v2.dot(this->edge1);
  float d21 = v2.dot(this->edge2);
  float denom = (d00 * d11)-(d01*d01);
  float v = (d11 * d20 - d01 * d21) / denom;
  float w = (d00 * d21 - d01 * d20) / denom;
  float u = 1.0 - v - w;
  vec normal = (this->vertex1_norm * u) + (this->vertex2_norm * v) + (this->vertex3_norm * w);
  // vec normal = this->vertex1_norm;
  // this->normal_vector = normal;
  return normal;
}

//returns the base color of the triangle
material * triangle::get_material() const {
  return this->geo_material;
}

//returns triangle bounding box
aabb triangle::bounding_box() const {
  return this->box;
}
