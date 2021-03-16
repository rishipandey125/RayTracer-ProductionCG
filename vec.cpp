#include "vec.h"
#include <cmath>
//Vector Class
//Default Constructor
vec::vec() {
  this->x = 0.0f;
  this->y = 0.0f;
  this->z = 0.0f;
}

/*
Specific Constructor
@param i,j,k: values of the 3d vector
*/
vec::vec(float i, float j, float k) {
  this->x = i;
  this->y = j;
  this->z = k;
}

//Calculate and Return the Length of the Vector (Magnitude)
float vec::length() {
  return sqrt((this->x*this->x)+(this->y*this->y)+(this->z*this->z));
}

//Set the given vector to be a unit vector (length == 1)
void vec::unit() {
  float length = this->length();
  this->x = this->x/length;
  this->y = this->y/length;
  this->z = this->z/length;
}

/*
Dot Function:
@param vector: vector to dot with current vector
@return float value of dot product
*/
float vec::dot(const vec &vector) const {
  return (this->x * vector.x) + (this->y * vector.y) + (this->z * vector.z);
}

/*
Cross Function:
@param vector: vector to cross with current vector
@return vec product of cross
*/
vec vec::cross(const vec &vector) {
  float x = (this->y*vector.z) - (this->z*vector.y);
  float y = -1.0*((this->x*vector.z) - (this->z*vector.x));
  float z = (this->x*vector.y) - (this->y*vector.x);
  return vec(x,y,z);
}

/*
Add Override Function:
@param vector: vector to add with current vector
@return vec that is the sum between the two vectors
*/
vec vec::operator+(const vec &vector) {
  return vec(this->x+vector.x, this->y+vector.y, this->z+vector.z);
}

/*
Subtract Override Function:
@param vector: vector to subtract with current vector
@return vec that is the difference between the two vectors
*/
vec vec::operator-(const vec &vector) const {
  return vec(this->x-vector.x, this->y-vector.y, this->z-vector.z);
}

/*
Equal Override Function:
@param vector: vector to equate current vector to
*/
void vec::operator=(const vec &vector) {
  this->x = vector.x;
  this->y = vector.y;
  this->z = vector.z;
}

/*
Multiply Override Function:
@param vector: vector to multiply with current vector
@return vec that is the product between the two vectors
*/
vec vec::operator*(const vec &vector) {
  return vec(this->x*vector.x, this->y*vector.y, this->z*vector.z);
}

/*
Multiply Override Function: (Scalar)
@param scalar: scalar to multiply with current vector
@return vec that is the product between the vector and scalar
*/
vec vec::operator*(const float &scalar) const {
  return vec(this->x*scalar, this->y*scalar, this->z*scalar);
}

/*
Divide Override Function: (Scalar)
@param scalar: scalar to divide with current vector
@return vec that is the division between the vector and scalar
*/
vec vec::operator/(const float &scalar) {
  return vec(this->x/scalar, this->y/scalar, this->z/scalar);
}

/*
Comparison Override Function:
@param vector: vector to compare with current vector
@return: true if they are the same (all values are the same in each vector), false otherwise
*/
bool vec::operator==(const vec &vector) {
  if ((this->x == vector.x) && (this->y == vector.y) && (this->z == vector.z)) {
    return true;
  }
  return false;
}

float vec::operator[](const int index) {
  if (index == 0) {
    return this->x;
  } else if (index == 1) {
    return this->y;
  } else if (index == 2) {
    return this->z;
  }
  std::cerr << "INDEX OUT OF BOUNDS FOR VEC[]" << std::endl;
  throw 1;
}

/*
Clamp Function
Clamps the RGB values between 0 and 1
*/
void vec::clamp() {
  if (this->x > 1.0) {
    this->x = 1.0;
  } else if (this->x <= 0.0) {
    this->x = 0.0;
  }
  if (this->y > 1.0) {
    this->y = 1.0;
  } else if (this->y <= 0.0) {
    this->y = 0.0;
  }
  if (this->z > 1.0) {
    this->z = 1.0;
  } else if (this->z <= 0.0) {
    this->z = 0.0;
  }
}

//Sets the vector to be the square root of itself
void vec::root() {
  this->x = sqrt(this->x);
  this->y = sqrt(this->y);
  this->z = sqrt(this->z);
}

//Prints the vector for debugging
void vec::print() {
  std::cout << "<" <<  this->x << "," << this->y << "," << this->z << ">" << std::endl;
}
