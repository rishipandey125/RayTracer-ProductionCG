#include <iostream>
#include "vec.cpp"
#include "ray.cpp"
#include "camera.cpp"
// perspective rendering: set origin and fire ray through viewport
// orthogonal rendering: fire ray direct from each grid point in the viewport
  //build viewport around camera origin

void render_frame() {
  camera cam(point(0,0,0),point(0,0,-1),-1,16/9,2);
  int image_width = 500;
  int image_height = (int)(image_width/cam.aspect_ratio);
  std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";
  for (int j = image_height-1; j >= 0; j--) {
    for (int i = 0; i < image_width; i++) {
      float u = float(i)/image_width;
      float v = float(j)/image_width;
      cam.cast_perspective_ray(u,v);
      color red(1.0,0,0);
      int r = static_cast<int>(255*red.x);
      int g = static_cast<int>(255*red.y);
      int b = static_cast<int>(255*red.z);
      std::cout << r << ' ' << g << ' ' << b << '\n';
    }
  }
}
