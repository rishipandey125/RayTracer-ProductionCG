#include "sphere.h"
#include <cmath>
sphere::sphere() {}

sphere::sphere(point sphere_center, float sphere_radius, color geo_base_color) {
  this->center = sphere_center;
  this->radius = sphere_radius;
  this->base_color = geo_base_color;
}

float sphere::hit(ray &casted_ray) const {
  vec ac = casted_ray.origin-this->center;
  float a = casted_ray.direction.dot(casted_ray.direction);
  float b = 2*casted_ray.direction.dot(ac);
  float c = ac.dot(ac) - (this->radius*this->radius);
  float discriminant = (b*b)-(4*a*c);
  if (discriminant > 0.0)  {
    return ((-b-sqrt(discriminant))/(2*a));
  }
  return -1.0;
}

vec sphere::get_normal_vector(point &point_on_sphere) const {
  return point_on_sphere-this->center;
}

color sphere::get_base_color() const {
  return this->base_color;
}
