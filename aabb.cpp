#include "aabb.h"
//AABB Class

//Default Constructor
aabb::aabb() {}

/*
Specific Constructor:
@param a: minimum point of the aabb
@param b: maximum point of the aabb
*/
aabb::aabb(point a, point b) {
  this->minimum = a;
  this->maximum = b;
}

/*
Hit Function for AABB:
@param casted_ray: ray casted at geometry
@return: -1 for no hit, and 1 for hit
*/
float sphere::hit(ray &casted_ray) const {
  for (int a = 0; a < 3; a++) {
    float t0 = this->minimum
    float t1 =
    float tmin = fmax(t0,t_min);
    float tmax = fmin(t1,t_max);
    if (tmax <= tmin) {
      return -1.0;
    }
  }
  return 1.0;
}

/*
NOT USED just overriden
*/
vec aabb::get_normal_vector(point &point_on_sphere) const {
  return vec(0,0,0);
}

/*
NOT USED just overriden
*/
color aabb::get_base_color() const {
  return vec(0,0,0);
}
