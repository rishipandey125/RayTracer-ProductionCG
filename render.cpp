#include <iostream>
#include "vec.cpp"
#include "ray.cpp"
#include "random.cpp"
#include "aabb.cpp"
#include "geometry.h"
#include "hittables.cpp"
#include "camera.cpp"
#include "sphere.cpp"
#include <vector>

//Render File
//Constant Epsilon
const float EPSILON = 0.0001;

/*
Trace function, traces rays through the scene based on the trace depth, and materials of the hit objects.
@param casted_ray: ray casted into the scene
@param tree: the bvh tree of scene Geometry
@param depth: depth of ray bounces
@return the color after tracing
*/
color trace(ray &casted_ray, geometry &scene_geometry, int depth) {
  if (depth <= 0) {
    return color(0,0,0);
  }
  hit_record rec;
  if (scene_geometry.hit(casted_ray,0.001,float(RAND_MAX),rec)) {
    ray next_ray;
    if (rec.geo_material->scatter(casted_ray,rec,next_ray)) {
      return trace(next_ray,scene_geometry,depth-1)*rec.geo_material->base_color + rec.geo_material->emitted();
    } else {
      return rec.geo_material->emitted();
    }
  }
  //gradient sky (global illumination)
  vec unit_direction = casted_ray.direction;
  unit_direction.unit();
  float val = (unit_direction.y+1.0)/2.0;
  // return color();
  return color(1.0, 1.0, 1.0)*(1-val) + color(0.5, 0.7, 1.0)*val;
}

/*
Correctly Outputting Averaged Pixel Color After Multi-Jitter Sampling:
@param pixel: pixel color after sampling
@param samples: number of samples
@return output_pixel: correct pixel color
*/
color output_color(color &pixel, int samples) {
  float ratio = 1.0/float(samples);
  color output_pixel = pixel*ratio;
  //gamma correction gamma = 2.0
  output_pixel.root();
  output_pixel.clamp();
  return output_pixel;
}


//Function to Render Image
void render_frame() {
  // Creating Scene Geometry
  //Creating a Camera
  camera cam(point(0,0,0),point(0,0,-1),16.0/9.0,90.0,0.0);
  //Image Sizes
  int image_width = 1000;

  int image_height = (int)(image_width/cam.aspect_ratio);
  // Creating Scene Geometry
  //floor
  hittables scene_geometry;
  scene_geometry.add(new sphere(point(0,-100.5,-1),100,new diffuse(color(0.7,.7,.7))));
  scene_geometry.add(new sphere(point(0,0,-1),0.5,new diffuse(color(0.578,.439,.856))));

  //Creating BVH
  //Setting Up PPM Output
  std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";
  //Number of Samples per Pixel
  int samples = 50;
  int depth = 50;
  //Iterating Through Image Size
  for (int j = image_height-1; j >= 0; j--) {
    for (int i = 0; i < image_width; i++) {
      color shade; //initializes shade color to (0,0,0) which is black - the background
      //fire rays for samples
      for (int s = 0; s < samples; s++) {
          //use the multi-jitter shuffled samples
        float u = (float(i)+random_float())/image_width;
        float v = (float(j)+random_float())/image_height;
          //cast ray into the scene
        ray casted_ray = cam.cast_perspective_ray(u,v);
          //trace some gosh darn rays
        shade = shade + trace(casted_ray,scene_geometry,depth);
      }
      //get the correct output color
      color output = output_color(shade,samples);
      //output to ppm
      int r = static_cast<int>(255*output.x);
      int g = static_cast<int>(255*output.y);
      int b = static_cast<int>(255*output.z);
      std::cout << r << ' ' << g << ' ' << b << '\n';
    }
  }

}
