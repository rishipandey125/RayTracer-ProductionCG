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

aabb aabb::surrounding_box(aabb &box1, aabb &box2) {
  point min = point(fmin(box1.minimum.x,box2.minimum.x),
  fmin(box1.minimum.y,box2.minimum.y),
  fmin(box1.minimum.z,box2.minimum.z));

  point max = point(fmin(box1.maximum.x,box2.maximum.x),
  fmin(box1.maximum.y,box2.maximum.y),
  fmin(box1.maximum.z,box2.maximum.z));

  return aabb(min,max);
}
