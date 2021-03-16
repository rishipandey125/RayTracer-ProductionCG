#ifndef VEC_H
#define VEC_H
//Header File for the Vector Class
class vec {
  public:
    //constructors
    vec();
    vec(float i, float j, float k);
    //math helper functionss
    float length();
    void unit();
    float dot(const vec &vector) const;
    vec cross(const vec &vector);
    vec operator+(const vec &vector);
    vec operator-(const vec &vector) const;
    void operator=(const vec &vector);
    vec operator*(const vec &vector);
    vec operator*(const float &scalar) const;
    vec operator/(const float &scalar);
    bool operator==(const vec &vector);
    float operator[] (const int index);
    //rgb clamp helper function
    void clamp();
    //extra function (only used in gamma correction currently)
    void root();
    //helper print funcction
    void print();
    //member variables
    float x,y,z;

};
//aliases for creating points and colors with the same structure
using point = vec;
using color = vec;
#endif
