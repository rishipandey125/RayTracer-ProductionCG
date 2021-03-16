#pragma once
#include <cstdlib>
#include <cmath>
#include "vec.h"
//Random Class
//Generate Random Float from 0 to 1
float random_float() {
  return ((float) rand()/RAND_MAX);
}

//Generates Random Float between min and max
float random_float(float min, float max) {
  return min + ((max-min)*random_float());
}

int random_int(int min, int max) {
  return min + ((max-min)*(rand()/RAND_MAX));
}
