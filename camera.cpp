#include "camera.h"

camera::camera() {}

camera::camera(point &camera_origin, point &camera_look_at, float &camera_focal_length, float &camera_aspect_ratio, float &camera_viewport_height) {
  this->origin = camera_origin;
  this->look_at = camera_look_at;
  this->focal_length = camera_focal_length;
  this->aspect_ratio = camera_aspect_ratio;
  this->viewport_height = camera_viewport_height;
  this->viewport_width = camera_viewport_height*camera_aspect_ratio;
  this->horizontal = vec(this->viewport_width,0,0);
  this->vertical = vec(0,this->viewport_height,0);
  this->lower_left_corner = this->origin-(this->horizontal/2.0)-(this->vertical/2.0)-vec(0,0,this->focal_length);

}

camera::ray cast_perspective_ray(float &u, float &v) {
  point viewport_point = this->lower_left_corner + (this->horizontal*u) + (this->vertical*v);
  vec direction = viewport_point-this->origin;
  return ray(this->origin,direction);
}

camera::ray cast_orthogonal_ray(float &u, float &v) {
  point lower_left_viewport_point = this->origin-(this->horizontal/2.0)-(this->vertical/2.0);
  point viewport_origin = lower_left_viewport_point + (this->horizontal*u) + (this->vertical*v);
  vec direction = viewport_origin-vec(0,0,1);
  return ray(viewport_origin,direction);
}
