#incude "ray.h"

ray::ray() {}

ray::ray(const point &ray_origin, const vec &ray_direction) {
  this->origin = ray_origin;
  this->direction = ray_direction;
}

point ray::get_point_at(float t) {
  return this->origin + (this->direction*t);
}
