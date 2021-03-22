#include "plane.h"
//Plane Class

//Default Constructor
plane::plane() {}

/*
Specific Constructor
@param plane_vertex1, plane_vertex2, plane_vertex3, plane_vertex4: vertex points for the plane
@param geo_base_color: color of the plane
*/
plane::plane(point plane_vertex1, point plane_vertex2, point plane_vertex3, point plane_vertex4, material * geo_material) {
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
  this->geo_material = geo_material;

  vec minimum = vec(compute_smallest(plane_vertex1.x,plane_vertex2.x,plane_vertex3.x,plane_vertex4.x),
                    compute_smallest(plane_vertex1.y,plane_vertex2.y,plane_vertex3.y,plane_vertex4.y),
                    compute_smallest(plane_vertex1.z,plane_vertex2.z,plane_vertex3.z,plane_vertex4.z));

  vec maximum = vec(compute_largest(plane_vertex1.x,plane_vertex2.x,plane_vertex3.x,plane_vertex4.x),
                    compute_largest(plane_vertex1.y,plane_vertex2.y,plane_vertex3.y,plane_vertex4.y),
                    compute_largest(plane_vertex1.z,plane_vertex2.z,plane_vertex3.z,plane_vertex4.z));
  //compute and set the bounding box for the rectangle
  this->box = aabb(minimum,maximum);
}

/*
Hit Function for Plane
@param casted_ray: ray casted from the camera (could be perspective or orthographic)
@return float: -1 if there is no hit, and t (parametric value on the ray) if there is a hit
*/
bool plane::hit(ray &casted_ray, double t_min, double t_max, hit_record &rec) const {
  vec n = this->normal_vector;
  point ao = this->vertex1-casted_ray.origin;
  float denom = casted_ray.direction.dot(n);
  float t = (ao.dot(n))/denom;
  if (t > 0.0) {
    if (t < t_min || t > t_max) {
      return false;
    }
    rec.t = t;
    rec.hit_point = casted_ray.get_point_at(t);
    rec.normal = this->get_normal_vector(rec.hit_point);
    rec.geo_material = this->get_material();
    return true;
  }
  return false;
}

//Retrieving Plane Normal Vector
vec plane::get_normal_vector(point &point_on_plane) const {
  return (this->normal_vector);
}

//Getting Material of the Plane
material * plane::get_material() const {
  return this->geo_material;
}

//NOT USED
aabb plane::bounding_box() const {
  return this->box;
}
