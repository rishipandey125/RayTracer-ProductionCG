#include "ray.h"
//Ray Class
//Default Constructor
ray::ray() {}

/*
Specified Constructor:
@param ray_origin: a point specifying the origin of the ray
@param ray_direction: the direction of the ray
*/
ray::ray(const point &ray_origin, vec &ray_direction) {
  ray_direction.unit();
  this->origin = ray_origin;
  this->direction = ray_direction;
}

/*
Function to Get Point on a Ray:
@param t: parametric value on ray
@return: point on ray at value t
*/
point ray::get_point_at(float t) {
  return this->origin + (this->direction*t);
}
