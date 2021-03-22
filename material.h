#ifndef MATERIAL_H
#define MATERIAL_H
#include "hit.h"
#include <cmath>

/*
Calculates the Reflection Vector Given the casted ray directin vector and normal vectors.
@param v: casted ray direction vector
@param n: normal vector
@return reflect: relction vector
*/
vec reflect(vec &v, vec &n) {
  float product = v.dot(n)*2.0;
  vec reflect = v - (n*product);
  return reflect;
}

/*
Material Class
Materials: Glass, Metal, and Diffuse
*/

class material {
  public:
    color base_color;
    material() {}
    virtual bool scatter(ray &casted_ray, hit_record &rec, ray &next_ray) {
      return false;
    }
};

/*
Diffuse material with a base color. The scatter function works similar to shader.
*/
class diffuse: public material {
  public:
    diffuse(color b_color) {
      base_color = b_color;
    }
    virtual bool scatter(ray &casted_ray, hit_record &rec, ray &next_ray) {
      point target = rec.hit_point + rec.normal + random_unit_vec();
      vec scatter = target-rec.hit_point;
      next_ray = ray(rec.hit_point,scatter);
      return true;
    }
};

class metal: public material {
  public:
    metal(color b_color, float f) {
      base_color = b_color;
      fuzz = f;
    }
    virtual bool scatter(ray &casted_ray, hit_record &rec, ray &next_ray) {
      vec r = reflect(casted_ray.direction, rec.normal);
      vec scatter = r + (random_unit_vec()*fuzz);
      next_ray = ray(rec.hit_point,scatter);
      if (next_ray.direction.dot(rec.normal) > 0) {
        return true;
      }
      return false;
    }
    float fuzz;
};
#endif
