#ifndef MATERIAL_H
#define MATERIAL_H
#include "hit.h"
#include <cmath>

/*
Calculates the Reflection Vector Given the casted ray directin vector and normal vectors.
@param v: casted ray direction vector
@param n: normal vector
@return reflect: relction vector
*/
vec reflect(vec &v, vec &n) {
  float product = v.dot(n)*2.0;
  vec reflect = v - (n*product);
  return reflect;
}

/*
Calculates the Refraction Vector
@param v: casted ray direction
@param n: normal vector
@param cos_theta:
@param ni_over_nt:
@return refraction vector
*/
vec refract(vec &v, vec &n ,float &cos_theta, float ni_over_nt) {
  vec r_out_perp = (v + (n*cos_theta))*ni_over_nt;
  float length = r_out_perp.length();
  vec r_out_parallel = n * -1.0 * sqrt(fabs(1.0-(length*length)));
  return r_out_perp + r_out_parallel;
}

//Schlicks Consant
float schlick(float cosine, float r_i) {
  float r0 = (1-r_i) / (1+r_i);
  r0 = r0*r0;
  return r0 + ((1-r0)*pow((1-cosine),5));
}

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

/*
Diffuse material with a base color. The scatter function works similar to shader.
*/
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

class metal: public material {
  public:
    metal(color b_color, float f) {
      base_color = b_color;
      fuzz = f;
    }
    virtual bool scatter(ray &casted_ray, hit_record &rec, ray &next_ray) {
      vec r = reflect(casted_ray.direction, rec.normal);
      vec scatter = r + (random_unit_vec()*fuzz);
      if (scatter.dot(rec.normal) > 0) {
        next_ray = ray(rec.hit_point,scatter);
        return true;
      }
      return false;
    }
    float fuzz;
};

class dielectric: public material {
  public:
    dielectric(float r_i) {
      base_color = color(1,1,1);
      refractive_index = r_i;
    }

    virtual bool scatter(ray &casted_ray, hit_record &rec, ray &next_ray) {
      vec dir = casted_ray.direction;
      vec n = rec.normal;
      float ni_over_nt;
      dir.unit();
      if (dir.dot(n) > 0) {
        n = n * -1.0;
        ni_over_nt = refractive_index;
      } else {
        ni_over_nt = 1.0/refractive_index;
      }
      float cosine = n.dot(dir*-1.0);
      float sin = sqrt(1.0-(cosine*cosine));
      if (ni_over_nt * sin > 1.0) {
        vec reflect_vec = reflect(dir,n);
        next_ray = ray(rec.hit_point,reflect_vec);
        return true;
      }
      vec scatter;
      if (random_float() < schlick(cosine,refractive_index)) {
        scatter = reflect(dir,n);
      } else {
        scatter = refract(dir,n,cosine,ni_over_nt);
      }
      next_ray = ray(rec.hit_point,scatter);
      return true;
    }
    float refractive_index;
};
#endif
