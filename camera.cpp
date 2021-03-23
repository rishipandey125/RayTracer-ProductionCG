#include "camera.h"
//Camera Class

//Default Constructor
camera::camera(){}
/*
Specific Constructor:
@param camera_origin: a point specifying the camera's origin
@param camera_look_at: point specifying where the camera should look
@camera_focal_length: float specifying the focal length of the camera
@camera_aspect_ratio: float specifying the aspect ratio of the image outputed by the camera sensor
@camera_viewport_height: float specifying the height of the viewport
*/
camera::camera(point camera_origin, point camera_look_at,
      float camera_focal_length, float camera_aspect_ratio,
      float v_fov) {
  this->origin = camera_origin;
  this->look_at = camera_look_at;
  this->focal_length = camera_focal_length;
  this->aspect_ratio = camera_aspect_ratio;
  float theta = v_fov * (M_PI/180.0);
  this->viewport_height = 2.0 * tan(theta/2.0);
  this->viewport_width = this->viewport_height*camera_aspect_ratio;
  this->horizontal = vec(this->viewport_width,0,0);
  this->vertical = vec(0,this->viewport_height,0);
  this->w = camera_origin-camera_look_at;
  w.unit();
  this->lower_left_corner = this->origin-(this->horizontal/2.0)-(this->vertical/2.0)-vec(0,0,this->focal_length)-w;

}

/*
Cast Perspective Ray Function:
@param u: the horizontal value of the image plane
@param v: the vertical value of the image plane
@return: a ray with its origin at the camera's origin and direction through the viewport
*/
ray camera::cast_perspective_ray(float &u, float &v) {
  point viewport_point = this->lower_left_corner + (this->horizontal*u) + (this->vertical*v);
  vec direction = viewport_point-this->origin;
  // direction.unit();
  return ray(this->origin,direction);
}

/*
Cast Orthographic Ray Function:
@param u: the horizontal value of the image plane
@param v: the vertical value of the image plane
@return: a ray with its origin at the viewport built around the camera origin and direction perpindicular
*/
ray camera::cast_orthogonal_ray(float &u, float &v) {
  point lower_left_viewport_point = this->lower_left_corner+vec(0,0,this->focal_length);
  point viewport_origin = lower_left_viewport_point + (this->horizontal*u) + (this->vertical*v);
  vec direction = viewport_origin-this->w;
  return ray(viewport_origin,direction);
}
