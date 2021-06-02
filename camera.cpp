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
camera::camera(point camera_origin, point camera_look_at, float camera_aspect_ratio,
      float v_fov, float apeture) {
  this->origin = camera_origin;
  this->look_at = camera_look_at;
  //calculate the focus distance length(where the camera is - what it is looking at)
  float focus_distance = (camera_origin-camera_look_at).length();
  //lens radius for how big the lens is based from aperture
  this->lens_radius = apeture/2.0;
  this->aspect_ratio = camera_aspect_ratio;
  //theta angle for FOV
  float theta = v_fov * (M_PI/180.0);
  //vector math for setting up the viewport
  this->viewport_height = 2.0 * tan(theta/2.0);
  this->viewport_width = this->viewport_height*this->aspect_ratio;
  this->w = camera_origin-camera_look_at;
  this->w.unit();
  this->u = vec(0,1,0).cross(this->w); this->u.unit();
  this->v = this->w.cross(this->u);
  this->horizontal = this->u * focus_distance * this->viewport_width;
  this->vertical = this->v * focus_distance * this->viewport_height;
  this->lower_left_corner = this->origin-(this->horizontal/2.0)-(this->vertical/2.0)-(this->w*focus_distance);
}

/*
Cast Perspective Ray Function:
@param u: the horizontal value of the image plane
@param v: the vertical value of the image plane
@return: a ray with its origin at the camera's origin and direction through the viewport
*/
ray camera::cast_perspective_ray(float &u, float &v) {
  //disk lens with lens radius
  vec lens = random_in_unit_disk()*this->lens_radius;
  //offset UV value
  vec offset = (this->u*lens.x) + (this->v*lens.y);
  point viewport_point = this->lower_left_corner + (this->horizontal*u) + (this->vertical*v);
  vec direction = viewport_point-this->origin-offset;
  return ray(this->origin+offset,direction);
}
