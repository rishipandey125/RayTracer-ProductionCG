#include <iostream>
#include "vec.cpp"
#include "ray.cpp"
#include "camera.cpp"
#include "geometry.h"
#include "sphere.cpp"
#include "triangle.cpp"
#include "plane.cpp"
#include "random.cpp"
#include <vector>

//Render File
//Constant Epsilon
const float EPSILON = 0.0001;

/*
Shading Function - Blinn-Phong Lambertian Shading and Shadows:
@param hit_point: the point to shade
@param normal_vector: the normal vector of the geometry at that point
@param point_light: location of the light source
@param base_color: base color of the geometry
@param scene_geometry: geometry in the scene to check for shadows
@return shade: color to shade the pixel
*/
color shading(point &hit_point, vec &normal_vector,point &point_light, color &base_color, std::vector<geometry*> scene_geometry) {
  vec light_vector = point_light-hit_point;
  light_vector.unit();
  vec epsilon(EPSILON,EPSILON,EPSILON);
  ray shadow_ray(hit_point+epsilon,light_vector);
  //shadow shading constant
  float shadow = 0.15;
  for (geometry *object : scene_geometry) {
    float t = object->hit(shadow_ray);
    if (t > 0.0) {
      //an object is casting a shadow
      shadow = 0.0;
      break;
    }
  }
  float diffuse = normal_vector.dot(light_vector);
  diffuse += shadow;
  color shade = base_color * diffuse;
  //clamping pixel values
  shade.clamp();
  return shade;
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
  //gamma correction
  output_pixel.root();
  output_pixel.clamp();
  return output_pixel;
}

//Function to Render Image
void render_frame() {
  //Creating a Camera
  camera cam(point(0,0,0),point(0,0,-1),1,1,2);
  //Creating a Point Light
  point point_light(.5,1,0);
  //Image Sizes
  int image_width = 1000;
  int image_height = (int)(image_width/cam.aspect_ratio);
  //Creating Scene Geometry
  plane floor(point(-1,-1,-1),point(-1,1,-10),point(1,1,-10),point(1,-1,-1),color(1,0,0));
  sphere ball(point(0,0,-3),.5,color(0,0,1));
  triangle tri(point(.1,-1,-2),point(0.4,-1,-2),point(0.25,.6,-2),color(0,1,0));
  std::vector<geometry*> scene_geometry = {&floor,&ball,&tri};
  //Setting Up PPM Output
  std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";
  //Number of Samples per Pixel
  int samples = 16;
  int sqrt_samples = sqrt(float(samples));
  float step_size = 1.0/float(sqrt_samples);
  //Iterating Through Image Size
  for (int j = image_height-1; j >= 0; j--) {
    for (int i = 0; i < image_width; i++) {
      color shade; //initializes shade color to (0,0,0) which is black - the background
      //multi-jitter sampling - iterate through each sub-square
      for (int ys = 0; ys < sqrt_samples; ys++) {
        for (int xs = 0; xs < sqrt_samples; xs++) {
          //one random sample in the sub-square
          float random_u = random_float(xs*step_size,(xs+1)*step_size);
          float random_v = random_float(ys*step_size,(ys+1)*step_size);
          float u = (float(i)+random_u)/image_width;
          float v = (float(j)+random_v)/image_width;
          //cast ray into the scene
          ray casted_ray = cam.cast_orthogonal_ray(u,v);
          float closest_t = float(RAND_MAX);
          geometry * closest_geometry;
          bool hit = false;
          //checking for a hit in the scene geometry
          for (int i = 0; i < scene_geometry.size(); i++) {
            float t = (scene_geometry[i])->hit(casted_ray);
            //if there is a hit and it is closer than the one before it
            if (t > 0.0 && t < closest_t) {
              closest_geometry = scene_geometry[i];
              closest_t = t;
              hit = true;
            }
          }
          //if a hit was found shade!
          if (hit) {
            point hit_point = casted_ray.get_point_at(closest_t);
            vec normal = (closest_geometry)->get_normal_vector(hit_point);
            //check to make sure the normal vector is facing the correct way
            if (normal.dot(casted_ray.direction) > 0.0) {
              normal = normal * -1.0;
            }
            normal.unit();
            color base_color = (closest_geometry)->get_base_color();
            //shade the pixel
            shade = shade + shading(hit_point,normal,point_light,base_color,scene_geometry);
          }
        }
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
