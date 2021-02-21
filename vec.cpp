#include "vec.h"
#include <cmath>
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

float vec::dot(const vec &vector) const {
  return (this->x * vector.x) + (this->y * vector.y) + (this->z * vector.z);
}

vec vec::cross(const vec &vector) {
  float x = (this->y*vector.z) - (this->z*vector.y);
  float y = -1.0*((this->x*vector.z) - (this->z*vector.x));
  float z = (this->x*vector.y) - (this->y*vector.x);
  return vec(x,y,z);
}

vec vec::operator+(const vec &vector) {
  return vec(this->x+vector.x, this->y+vector.y, this->z+vector.z);
}

vec vec::operator-(const vec &vector) const {
  return vec(this->x-vector.x, this->y-vector.y, this->z-vector.z);
}

void vec::operator=(const vec &vector) {
  this->x = vector.x;
  this->y = vector.y;
  this->z = vector.z;
}

vec vec::operator*(const vec &vector) {
  return vec(this->x*vector.x, this->y*vector.y, this->z*vector.z);
}

vec vec::operator*(const float &scalar) {
  return vec(this->x*scalar, this->y*scalar, this->z*scalar);
}

vec vec::operator/(const float &scalar) {
  return vec(this->x/scalar, this->y/scalar, this->z/scalar);
}

bool vec::operator==(const vec &vector) {
  if ((this->x == vector.x) && (this->y == vector.y) && (this->z == vector.z)) {
    return true;
  }
  return false;
}

void vec::clamp() {
  if (this->x > 1.0) {
    this->x = 1.0;
  } else if (this->x < 0.0) {
    this->x = 0.0;
  }
  if (this->y > 1.0) {
    this->y = 1.0;
  } else if (this->y < 0.0) {
    this->y = 0.0;
  }
  if (this->z > 1.0) {
    this->z = 1.0;
  } else if (this->z < 0.0) {
    this->z = 0.0;
  }
}

void vec::root() {
  this->x = sqrt(this->x);
  this->y = sqrt(this->y);
  this->z = sqrt(this->z);
}

void vec::print() {
  std::cout << "<" <<  this->x << "," << this->y << "," << this->z << ">" << std::endl;
}
