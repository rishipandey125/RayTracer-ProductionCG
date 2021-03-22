#ifndef HIT_H
#define HIT_H
#include "vec.h"
#include "ray.h"

class material;
//Hit Record for Hiting an Object
struct hit_record {
  point hit_point;
  vec normal;
  float t;
  material geo_material;
};
#endif
