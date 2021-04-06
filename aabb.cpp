#include "aabb.h"
#include <cmath>
//AABB Class

//Default Constructor
aabb::aabb() {
  this->minimum = vec();
  this->maximum = vec();
  this->centroid = vec();
}

/*
Specific Constructor:
@param a: minimum point of the aabb
@param b: maximum point of the aabb
*/
aabb::aabb(point a, point b) {
  this->minimum = a;
  this->maximum = b;
  this->centroid = (a+b)*0.5;

}

/*
Equal Overload:
@param box: box to compare
*/
void aabb::operator=(const aabb &box) {
  this->minimum = box.minimum;
  this->maximum = box.maximum;
  this->centroid = box.centroid;
}

/*
Hit Function for AABB:
@param casted_ray: ray casted at geometry
@param float t_min: min t parametric value
@param float t_max: max t parametric value
@return: false for no hit, and true for hit
*/
bool aabb::check_hit(ray &casted_ray, float t_min, float t_max) {
  for (int i = 0; i < 3; i++) {
    float min_val = (this->minimum[i]-casted_ray.origin[i]) / casted_ray.direction[i];
    float max_val = (this->maximum[i]-casted_ray.origin[i]) / casted_ray.direction[i];
    float t0 = fmin(min_val,max_val);
    float t1 = fmax(min_val,max_val);
    t_min = fmax(t0,t_min);
    t_max = fmin(t1,t_max);
    if (t_max <= t_min) {
      return false;
    }
  }
  return true;
}

/*
Creating Surrounding Box for AABB:
@param box: box to help create surronding box with the current box
@return: the surrounding box
*/
aabb aabb::surrounding_box(aabb &box) {
  point min = point(fmin(this->minimum.x,box.minimum.x),
  fmin(this->minimum.y,box.minimum.y),
  fmin(this->minimum.z,box.minimum.z));

  point max = point(fmax(this->maximum.x,box.maximum.x),
  fmax(this->maximum.y,box.maximum.y),
  fmax(this->maximum.z,box.maximum.z));
  return aabb(min,max);
}
