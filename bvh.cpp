#include "bvh.h"


point get_midpoint(std::vector<geometry*> &scene_geometry) {
  point midpoint = point();
  for (int i = 0; i < scene_geometry.size(); i++) {
    midpoint = midpoint + scene_geometry[i]->bounding_box().centroid;
  }
  midpoint = midpoint/scene_geometry.size();
  return midpoint;
}

aabb geometry_box(std::vector<geometry*> &scene_geometry) {
  aabb output_box = scene_geometry[0]->bounding_box();
  aabb second_box = aabb();
  for (int i = 1; i < scene_geometry.size(); i++) {
    second_box = scene_geometry[i]->bounding_box();
    output_box = output_box.surrounding_box(second_box);
  }
  return output_box;
}

bvh::bvh() {}

//This is where we create the tree
bvh::bvh(std::vector<geometry*> scene_geometry, int num_geo) {
  //if the data is less than num_geo then make a leaf
  aabb output_box = geometry_box(scene_geometry);
   if (scene_geometry.size() <= num_geo) {
    this->leaf_geometry = &scene_geometry;
    this->left = NULL;
    this->right = NULL;
    this->box = geometry_box(scene_geometry);
    this->leaf = true;
    //create a leaf
  } else {
    this->leaf_geometry = NULL;
    //get the bounding box of the scene geometry
    this->box = output_box;
    //partition the data and make a left and right node    this->left = bvh(left_scene_geometry, num_geo);
    std::vector<geometry*> left_scene_geometry;
    std::vector<geometry*> right_scene_geometry;
    point midpoint = get_midpoint(scene_geometry);
    // int index = random_int(0,2);
    int index = 1;
    for (int i = 0; i < scene_geometry.size(); i++) {
      if (scene_geometry[i]->bounding_box().centroid[index] < midpoint[index]) {
        left_scene_geometry.push_back(scene_geometry[i]);
      } else {
        right_scene_geometry.push_back(scene_geometry[i]);
      }
    }
    bvh left_node = bvh(left_scene_geometry,num_geo);
    bvh right_node = bvh(right_scene_geometry,num_geo);
    this->left = &left_node;
    this->right = &right_node;
    this->box = this->left->box.surrounding_box(this->right->box);
    this->leaf = false;
  }
}

float bvh::hit(ray &casted_ray) const {
  aabb bb = this->box;
  float t = bb.check_hit(casted_ray);
  return t;
}

/*
Getting the Normal Vector of the Point on the Sphere
@param point_on_sphere: point to get normal vector at
@return: normal vector
*/
vec bvh::get_normal_vector(point &point_on_sphere) const {
  return vec();
}

/*
@return the base color of the sphere
*/
color bvh::get_base_color() const {
  return vec();
}

aabb bvh::bounding_box() const {
  return this->box;
}
