#include "vec.h"
#incude <cmath>
using std::sqrt;

vec::vec() {
  this->x = 0.0f;
  this->y = 0.0f;
  this->z = 0.0f;
}

vec::vec(float i, float j, float k) {
  this->x = i;
  this->y = j;
  this->z = k;
}

float vec::length() {
  return sqrt((this->x*this->x)+(this->y*this->y)+(this->z*this->z));
}

void vec::unit() {
  float length = this->length();
  this->x = this->x/length;
  this->y = this->y/length;
  this->z = this->z/length;
}

float vec::dot(const vec &vector) {
  return (this->x * vector.x) + (this->y * vector.y) + (this->z * vector.z);
}
