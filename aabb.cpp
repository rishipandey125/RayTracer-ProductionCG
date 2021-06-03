#include "aabb.h"
aabb::aabb() {}

aabb::aabb(point bottom_left, point top_right) {
  this->min = bottom_left;
  this->max = top_right;
  this->centroid = (bottom_left+top_right)*0.5;
}

void aabb::operator=(const aabb &box) {
  this->min = box.min;
  this->max = box.max;
  this->centroid = box.centroid;
}

bool aabb::check_hit(ray &casted_ray, float t_min, float t_max) {
  for (int i = 0; i < 3; i++) {
    float min_val = (this->min[i]-casted_ray.origin[i]) / casted_ray.direction[i];
    float max_val = (this->max[i]-casted_ray.origin[i]) / casted_ray.direction[i];
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


aabb aabb::surrounding_box(aabb &box) {
  point min = point(fmin(this->min.x,box.min.x),
  fmin(this->min.y,box.min.y),
  fmin(this->min.z,box.min.z));

  point max = point(fmax(this->max.x,box.max.x),
  fmax(this->max.y,box.max.y),
  fmax(this->max.z,box.max.z));
  return aabb(min,max);
}
