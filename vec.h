#indef VEC_H
#define VEC_H

class vec {
  public:
    vec();
    vec(float i, float j, float k);
    float length();
    void unit();
    float dot(const vec &vector);
    vec cross(const vec &vector);
    vec operator+(const vec &vector);
    vec operator-(const vec &vector);
    void operator=(const vec &vector);
    vec operator*(const vec &vector);
    vec operator*(const float &scalar);
    vec operator/(const float &scalar);
    bool operator==(const vec &vector);
    void clamp();
    void root();
    void print();
    float x,y,z;

};
using point = vec;
using color = vec;
#endif
