#pragma once
#include <cstdlib>
#include <cmath>
#include "vec.h"

float random_float() {
  return ((float) rand()/RAND_MAX);
}

//Generates Random Float between min and max
float random_float(float min, float max) {
  return min + ((max-min)*random_float());
}
