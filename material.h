#ifndef MATERIAL_H
#define MATERIAL_H
#include "hit.h"
#include <cmath>

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
#endif