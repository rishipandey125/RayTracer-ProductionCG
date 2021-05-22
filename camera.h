#ifndef CAMERA_H
#define CAMERA_H
//Header File for Camera Class
class camera {
  public:
    //Default Constructor
    camera();
    //Specified Constructor
    camera(point camera_origin, point camera_look_at, float camera_aspect_ratio,
          float v_fov, float apeture);
    //Cast Perspective Ray Function
    ray cast_perspective_ray(float &u, float &v);
    //Camera Parameters
    point origin;
    point look_at;
    float aspect_ratio;
    float viewport_height;
    float lens_radius;
    //Calculated Ray Helper Vectors
    float viewport_width;
    point lower_left_corner;
    vec horizontal;
    vec vertical;
    vec u,v,w;

};

#endif
