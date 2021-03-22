#ifndef HIT_H
#define HIT_H

class material;

// Structure for When a Ray Hits an Object
struct hit_record {
  point hit_point;
  vec normal;
  float t;
  material *geo_material;
};
#endif
