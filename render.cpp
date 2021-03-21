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

/*
OBJ Loading Function:
@return hittables: mesh of triangles in the form of a hittables
*/
hittables load_obj_file(std::string inputfile) {
  tinyobj::ObjReaderConfig reader_config;

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

  auto& attrib = reader.GetAttrib();
  auto& shapes = reader.GetShapes();
  // auto& materials = reader.GetMaterials();
  hittables mesh;
  std::vector <vec> vertices = {};
  // Loop over shapes
  for (size_t s = 0; s < shapes.size(); s++) {
    // Loop over faces(polygon)
    size_t index_offset = 0;
    //Loop Over Each Triangle
    for (size_t f = 0; f < shapes[s].mesh.num_face_vertices.size(); f++) {
      int fv = shapes[s].mesh.num_face_vertices[f];
      // Loop over vertices in the face.
      for (size_t v = 0; v < fv; v++) {
        // access to vertex
        tinyobj::index_t idx = shapes[s].mesh.indices[index_offset + v];
        tinyobj::real_t vx = attrib.vertices[3*idx.vertex_index+0];
        tinyobj::real_t vy = attrib.vertices[3*idx.vertex_index+1];
        tinyobj::real_t vz = attrib.vertices[3*idx.vertex_index+2];
        vertices.push_back(vec(vx,vy,vz));
      }
      index_offset += fv;
      // per-face material
      shapes[s].mesh.material_ids[f];
    }
  }

  std::vector <vec> vertex_normals = {};
  for (int i = 0; i < attrib.vertices.size() / 3; i++) {
      vertex_normals.push_back(vec());
  }

  int num_triangles = vertices.size()/3;
  for (int i = 0; i < num_triangles; i++) {
    vec vertex1 = vertices[i*3];
    vec vertex2 = vertices[(i*3)+1];
    vec vertex3 = vertices[(i*3)+2];
    vec edge1 = vertex2 - vertex1;
    vec edge2 = vertex3 - vertex1;
    vec face_normal = edge1.cross(edge2);

    for (int x = 0; x < 3; x++) {
      int idx = shapes[0].mesh.indices[3*i+x].vertex_index;
      vertex_normals[idx] = vertex_normals[idx] + face_normal;
    }
  }
  //create the mesh
  for (int i = 0; i < num_triangles; i++) {
    vec vertex1 = vertices[i*3];
    vec vertex2 = vertices[(i*3)+1];
    vec vertex3 = vertices[(i*3)+2];
    int idx1 = shapes[0].mesh.indices[3*i].vertex_index;
    int idx2 = shapes[0].mesh.indices[3*i+1].vertex_index;
    int idx3 = shapes[0].mesh.indices[3*i+2].vertex_index;
    vec v_n1 = vertex_normals[idx1];
    vec v_n2 = vertex_normals[idx2];
    vec v_n3 = vertex_normals[idx3];
    v_n1.unit(); v_n2.unit(); v_n3.unit();
    mesh.add(new triangle(vertex1,vertex2,vertex3,v_n1,v_n2,v_n3,color(1,0,0)));
  }

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
color shading(point &hit_point,point &camera_origin, vec &normal_vector,point &point_light, color &base_color) {
  vec light_vector = point_light-hit_point;
  light_vector.unit();
  vec view = camera_origin-hit_point;
  view.unit();
  vec epsilon(EPSILON,EPSILON,EPSILON);
  // ray shadow_ray(hit_point+epsilon,light_vector);
  //shadow shading constant
  // float shadow = 0.15;
  float diffuse = normal_vector.dot(light_vector);
  // diffuse += shadow;
  //add specular component here
  vec h = light_vector + view;
  h.unit();
  //ks = 0.2 & n = 200
  float specular = 0.5 * fmax(pow(normal_vector.dot(h),200.0),0.0);
  color shade = base_color * (diffuse+specular);
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
  hittables scene_geometry;
  //Creating a Camera
  camera cam(point(0,0,0),point(0,0,-1),1,1,2);
  //Creating a Point Light
  point point_light(1.5,1,-0.5);
  //Image Sizes
  int image_width = 1000/2;
  int image_height = (int)(image_width/cam.aspect_ratio);
  // Creating Scene Geometry
  scene_geometry.add(new plane(point(-5,-3,0),point(5,-2,0),point(-5,-3,-100),point(5,-3,-100),color(1,0,0)));
  scene_geometry.add(new sphere(point(0,0,-6),1.0,color(0,1,0)));
  scene_geometry.add(new sphere(point(2,0,-8),1.0,color(0,0,1)));
  //Creating BVH
  bvh bvh_t = bvh(scene_geometry.geo,10);
  //Setting Up PPM Output
  std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";
  //Number of Samples per Pixel
  int samples = 16;
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
          if (bvh_t.hit(casted_ray,0.0,RAND_MAX,rec)) {
            point hit_point = rec.hit_point;
            vec normal = rec.normal;
            //check to make sure the normal vector is facing the correct way
            if (normal.dot(casted_ray.direction) > 0.0) {
              normal = normal * -1.0;
            }
            normal.unit();
            color base_color = rec.base_color;
            //shade the pixel
            shade = shade + shading(hit_point,cam.origin,normal,point_light,base_color);
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
