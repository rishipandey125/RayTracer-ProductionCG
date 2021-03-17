#include <iostream>
#include "vec.cpp"
#include "ray.cpp"
#include "aabb.cpp"
#include "bvh.cpp"
#include "camera.cpp"
#include "geometry.h"
#include "sphere.cpp"
#include "triangle.cpp"
#include "plane.cpp"
#include "hittables.cpp"
#include "random.cpp"
#include <vector>

//Render File
//Constant Epsilon
const float EPSILON = 0.0001;

std::vector<geometry*> * traverse_bvh(bvh *bvh_tree,ray &casted_ray) {
  //this is printing for each ray there is no hit
  if (bvh_tree->hit(casted_ray) > 0.0) {
    // std::cout << "hit" << std::endl;
    if (bvh_tree->leaf) {
      // bvh_tree.box.centroid.print();
      return &(bvh_tree->leaf_geometry);
    } else {
      // std::cout << "traversing" << std::endl;
      float t_left = bvh_tree->left->hit(casted_ray);
      float t_right = bvh_tree->right->hit(casted_ray);
      if (t_left > 0.0 && t_right > 0.0) {
        if (t_left < t_right) {
          return traverse_bvh(bvh_tree->right,casted_ray);
        } else {
          return traverse_bvh(bvh_tree->right,casted_ray);
        }
      } else if (t_left > 0.0) {
        return traverse_bvh(bvh_tree->left,casted_ray);
      } else if (t_right > 0.0) {
        return traverse_bvh(bvh_tree->right,casted_ray);
      }
    }
  }
  return NULL;
}


/*
Shading Function - Blinn-Phong Lambertian Shading and Shadows:
@param hit_point: the point to shade
@param normal_vector: the normal vector of the geometry at that point
@param point_light: location of the light source
@param base_color: base color of the geometry
@param scene_geometry: geometry in the scene to check for shadows
@return shade: color to shade the pixel
*/
color shading(point &hit_point, vec &normal_vector,point &point_light, color &base_color, bvh &bvh_t) {
  vec light_vector = point_light-hit_point;
  light_vector.unit();
  vec epsilon(EPSILON,EPSILON,EPSILON);
  ray shadow_ray(hit_point+epsilon,light_vector);
  //shadow shading constant
  float shadow = 0.15;
  //include bvh here
  // std::vector<geometry*> * leaf_geometry;
  // leaf_geometry = traverse_bvh(&bvh_t,shadow_ray);
  // if (leaf_geometry != NULL) {
  //   std::vector<geometry*> geo = *leaf_geometry;
  //   for (geometry *object : geo) {
  //     float t = object->hit(shadow_ray);
  //     if (t > 0.0) {
  //       //an object is casting a shadow
  //       shadow = 0.0;
  //       break;
  //     }
  //   }
  // }
  float diffuse = normal_vector.dot(light_vector);
  diffuse += shadow;
  //add specular component here
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
  int num_spheres = 100;
  // sphere ball(point(0,0,-3),.5,color(0,0,1));
  // sphere ball2(point(-1,0,-3),.5,color(0,1,1));
  std::vector<geometry*> scene_geometry;
  for (int i = 0; i < num_spheres; i++) {
    sphere * ball = new sphere(point(random_float(-1,1),random_float(-1,1),random_float(-20.0,-100.0)), 0.5, color(1,0,0));
    scene_geometry.push_back(ball);
  }
  bvh bvh_t = bvh(scene_geometry,5);
  //Setting Up PPM Output
  std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";
  //Number of Samples per Pixel
  int samples = 1;
  int sqrt_samples = sqrt(float(samples));
  //Creating Canonical Arrangement: From Pixar Paper (Correlated Multi-Jitter Sampling)
  float canonical[sqrt_samples][sqrt_samples][2];
  float n = float(sqrt_samples);
  for (int j = 0; j < sqrt_samples; j++) {
    for (int i = 0; i < sqrt_samples; i++) {
      canonical[j][i][0] = (i + (j+random_float())/n)/n;
      canonical[j][i][1] = (j + (i+random_float())/n)/n;
    }
  }
  //Iterating Through Image Size
  for (int j = image_height-1; j >= 0; j--) {
    for (int i = 0; i < image_width; i++) {
      color shade; //initializes shade color to (0,0,0) which is black - the background
      //multi-jitter sampling - shuffle canonical arrangement
      //preserving n-rooks
      for (int y = 0; y < sqrt_samples; y++) {
        for (int x = 0; x < sqrt_samples; x++) {
          int k = y + random_float() * (sqrt_samples-y);
          std::swap(canonical[y][x][0],canonical[k][x][0]);
        }
      }
      for (int x = 0; x < sqrt_samples; x++) {
        for (int y = 0; y < sqrt_samples; y++) {
          int k = x + random_float() * (sqrt_samples-x);
          std::swap(canonical[y][x][1],canonical[y][k][1]);
        }
      }
      //n-rooks preserved next step...
      //fire rays for samples
      for (int ys = 0; ys < sqrt_samples; ys++) {
        for (int xs = 0; xs < sqrt_samples; xs++) {
          //use the multi-jitter shuffled samples
          float u = (float(i)+canonical[ys][xs][0])/image_width;
          float v = (float(j)+canonical[ys][xs][0])/image_width;
          //cast ray into the scene
          ray casted_ray = cam.cast_perspective_ray(u,v);
          float closest_t = float(RAND_MAX);
          geometry * closest_geometry;
          bool hit = false;


          //checking for a hit in the leaf geometry
          //go through the entire tree if you get to the bottom
          // save the geometry at the bottom into a vector and pass that next
          //otherwise skip that ray
          //fire at bvh node
          //if you hit, hit hte left and right
          //if you hit those keep going until you dont hit or you are at a leaf
          //if you are at a leaf
          //fire a ray at every piece of geometry in that vector
          //store hit information
          std::vector<geometry*> * leaf_geometry;
          leaf_geometry = traverse_bvh(&bvh_t,casted_ray); //this is the issue
          if (leaf_geometry != NULL) {
            // std::cout << "entered" << std::endl;
            std::vector<geometry*> geometry = *leaf_geometry;
            // std::cout << geometry.size() << std::endl;
            for (int i = 0; i < geometry.size(); i++) {
              // std::cout << geometry.size() << std::endl;
              // geometry[i]->get_base_color().print();
              float t = geometry[i]->hit(casted_ray);
              //if there is a hit and it is closer than the one before it
              if (t > 0.0 && t < closest_t) {
                closest_geometry = geometry[i];
                closest_t = t;
                hit = true;
              }
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
            shade = shade + shading(hit_point,normal,point_light,base_color,bvh_t);
          }
        }
      }
      //get the correct output color
      color output = output_color(shade,samples);
      //output to ppm
      int r = static_cast<int>(255*output.x);
      int g = static_cast<int>(255*output.y);
      int b = static_cast<int>(255*output.z);
      // std::cout << r << ' ' << g << ' ' << b << '\n';
    }
  }
}
