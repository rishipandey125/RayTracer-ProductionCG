#include <iostream>
#define TINYOBJLOADER_IMPLEMENTATION // define this in only *one* .cc
#include "tinyobjloader-master/tiny_obj_loader.h"
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

hittables load_obj_file(std::string inputfile) {
  tinyobj::ObjReaderConfig reader_config;
  // reader_config.mtl_search_path = "./"; // Path to material files

  tinyobj::ObjReader reader;

  if (!reader.ParseFromFile(inputfile, reader_config)) {
    if (!reader.Error().empty()) {
        std::cerr << "TinyObjReader: " << reader.Error();
    }
    exit(1);
  }

  if (!reader.Warning().empty()) {
    std::cout << "TinyObjReader: " << reader.Warning();
  }

  // auto& attrib = reader.GetAttrib();
  auto& shapes = reader.GetShapes();
  // auto& materials = reader.GetMaterials();
  hittables mesh;
  // Loop over shapes
  for (size_t s = 0; s < shapes.size(); s++) {
    // Loop over faces(polygon)
    size_t index_offset = 0;
    for (size_t f = 0; f < shapes[s].mesh.num_face_vertices.size(); f++) {
      int fv = shapes[s].mesh.num_face_vertices[f];
      point vertex1;
      point vertex2;
      point vertex3;
      // Loop over vertices in the face.
      for (size_t v = 0; v < fv; v++) {
        // access to vertex
        tinyobj::index_t idx = shapes[s].mesh.indices[index_offset + v];
        tinyobj::real_t vx = attrib.vertices[3*idx.vertex_index+0];
        tinyobj::real_t vy = attrib.vertices[3*idx.vertex_index+1];
        tinyobj::real_t vz = attrib.vertices[3*idx.vertex_index+2];
        point vertex(vx,vy,vz);
        if (v == 0) {
          vertex1 = vertex;
        } else if (v == 1) {
          vertex2 = vertex;
        } else if (v == 2) {
          vertex3 = vertex;
        };
        tinyobj::real_t nx = attrib.normals[3*idx.normal_index+0];
        tinyobj::real_t ny = attrib.normals[3*idx.normal_index+1];
        tinyobj::real_t nz = attrib.normals[3*idx.normal_index+2];
      }
      index_offset += fv;
      mesh.add(new triangle(vertex1,vertex2,vertex3,color(1,0,0)));
      // per-face material
      shapes[s].mesh.material_ids[f];
    }
  }
  // std::cerr << mesh.geo.size() << std::endl;
  return mesh;
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
color shading(point &hit_point, vec &normal_vector,point &point_light, color &base_color) {
  vec light_vector = point_light-hit_point;
  light_vector.unit();
  vec epsilon(EPSILON,EPSILON,EPSILON);
  // ray shadow_ray(hit_point+epsilon,light_vector);
  //shadow shading constant
  float shadow = 0.15;
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
  camera cam(point(0,7,15),point(0,0,0),1,1,2);
  //Creating a Point Light
  point point_light(.5,1,3);
  //Image Sizes
  int image_width = 1000/2;
  int image_height = (int)(image_width/cam.aspect_ratio);
  //Creating Scene Geometry
  int num_spheres = 1e4;

  hittables scene_geometry;
  scene_geometry = load_obj_file("teapot.obj");
  // for (int i = 0; i < num_spheres; i++) {
  //   color col_rand = color(random_float(),random_float(),random_float());
  //   scene_geometry.add(new sphere(point(random_float(-40,40),random_float(-40,40),random_float(-80.0,-150.0)), 1, col_rand));
  // }
  // bvh bvh_t = bvh(scene_geometry.geo,128);
  //Setting Up PPM Output
  std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";
  //Number of Samples per Pixel
  int samples = 2;
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
          hit_record rec;
          //if a hit was found shade!
          if (scene_geometry.hit(casted_ray,0.0,RAND_MAX,rec)) {
            point hit_point = rec.hit_point;
            vec normal = rec.normal;
            //check to make sure the normal vector is facing the correct way
            if (normal.dot(casted_ray.direction) > 0.0) {
              normal = normal * -1.0;
            }
            normal.unit();
            color base_color = rec.base_color;
            //shade the pixel
            shade = shade + shading(hit_point,normal,point_light,base_color);
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
