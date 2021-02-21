#include <iostream>
#include "vec.cpp"
#include "ray.cpp"
#include "camera.cpp"
#include "geometry.h"
#include "sphere.cpp"
#include "triangle.cpp"
#include "plane.cpp"
// perspective rendering: set origin and fire ray through viewport
// orthogonal rendering: fire ray direct from each grid point in the viewport
  //build viewport around camera origin
color blinn_phong_shading(point &hit_point, vec &normal_vector,point &point_light, color &base_color) {
  vec light_vector = point_light-hit_point;
  light_vector.unit();
  float diffuse = normal_vector.dot(light_vector);
  color shade = base_color * diffuse;
  shade.clamp();
  return shade;
}

void render_frame() {
  camera cam(point(0,0,0),point(0,0,-1),1,16/9,2);
  point point_light(.2,.5,0);
  int image_width = 500;
  int image_height = (int)(image_width/cam.aspect_ratio);
  triangle object(point(-1,-1,-2),point(-1,1,-10),point(1,1,-10),color(1,0,0));
  std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";
  color shade;
  for (int j = image_height-1; j >= 0; j--) {
    for (int i = 0; i < image_width; i++) {
      float u = float(i)/image_width;
      float v = float(j)/image_width;
      ray casted_ray = cam.cast_perspective_ray(u,v);
      float t = object.hit(casted_ray);
      if (t > 0.0) {
        point hit_point = casted_ray.get_point_at(t);
        vec normal = object.get_normal_vector(hit_point);
        normal.unit();
        if (normal.dot(casted_ray.direction) < 0.0) {
          // std::cout << "entered" << std::endl;
          normal = normal * -1.0;
        }
        // normal.print();
        // shade = object.base_color;
        shade = blinn_phong_shading(hit_point,normal,point_light,object.base_color);
      } else {
        shade = color(0,0,0);
      }
      int r = static_cast<int>(255*shade.x);
      int g = static_cast<int>(255*shade.y);
      int b = static_cast<int>(255*shade.z);
      std::cout << r << ' ' << g << ' ' << b << '\n';
    }
  }
}
