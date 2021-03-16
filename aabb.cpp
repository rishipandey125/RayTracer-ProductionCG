#include "aabb.h"
#include <cmath>
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
float aabb::hit(ray &casted_ray) const {
  for (int i = 0; i < 3; i++) {
    float min_val = (this->minimum[i]-casted_ray.origin()[i]) / casted_ray.direction()[i];
    float max_val = (this->maximum[i]-casted_ray.origin()[i]) / casted_ray.direction()[i];
    float t0 = fmin(min_val,max_val);
    float t1 = fmin(min_val,max_val);
    // float tmin = fmax(t0,t_min);
    // float tmax = fmin(t1,t_max);
    if (t1 <= t0) {
      return -1.0;
    }
  }
  return 1.0;
}

aabb aabb::surrounding_box(aabb &box) {
  point min = point(fmin(this->minimum.x,box.minimum.x),
  fmin(this->minimum.y,box.minimum.y),
  fmin(this->minimum.z,box.minimum.z));

  point max = point(fmin(this->maximum.x,box.maximum.x),
  fmin(this->maximum.y,box.maximum.y),
  fmin(this->maximum.z,box.maximum.z));

  return aabb(min,max);
}
