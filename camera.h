#ifndef CAMERA_H
#define CAMERA_H

class camera {
  public:
    camera();
    ray get_perspective_ray();
    ray get_orthogonal_ray();

};

#endif
