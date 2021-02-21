#include "plane.h"
//Plane Class

//Default Constructor
plane::plane() {}

/*
Specific Constructor
@param plane_vertex1, plane_vertex2, plane_vertex3, plane_vertex4: vertex points for the plane
@param geo_base_color: color of the plane
*/
plane::plane(point plane_vertex1, point plane_vertex2, point plane_vertex3, point plane_vertex4, color geo_base_color) {
  this->vertex1 = plane_vertex1;
  this->vertex2 = plane_vertex2;
  this->vertex3 = plane_vertex3;
  this->vertex4 = plane_vertex4;
  //Creating Edge 1
  this->edge1 = this->vertex2-this->vertex1;
  //Creating Edge 2
  this->edge2 = this->vertex3-this->vertex1;
  //Crossing Edge 1 and 2 for the Plane's Normal Vector
  this->normal_vector = ((this->edge1).cross(this->edge2));
  this->base_color = geo_base_color;
}

/*
Hit Function for Plane
@param casted_ray: ray casted from the camera (could be perspective or orthographic)
@return float: -1 if there is no hit, and t (parametric value on the ray) if there is a hit
*/
float plane::hit(ray &casted_ray) const {
  vec n = this->normal_vector;
  point ao = this->vertex1-casted_ray.origin;
  float denom = casted_ray.direction.dot(n);
  float t = (ao.dot(n))/denom;
  if (t > 0.0) {
    return t;
  }
  return -1.0;
}

//Retrieving Plane Normal Vector
vec plane::get_normal_vector(point &point_on_plane) const {
  return (this->normal_vector);
}

//Getting Base Color of Plane
color plane::get_base_color() const {
  return this->base_color;
}
