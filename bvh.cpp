#include "bvh.h"
#include <unistd.h>

//BVH Default Constructor
bvh::bvh() {}

/*
Get Midpoint of Geometry
@param geo: vector of geometry
*/
point get_midpoint(std::vector <geometry*> &geo) {
  point midpoint = point();
  for (int i = 0; i < geo.size(); i++) {
    midpoint = midpoint + geo[i]->get_bounding_box().centroid;
  }
  midpoint = midpoint/geo.size();
  return midpoint;
}

/*
BVH Specific Constructor
@param scene_geometry: vector of geometry
@param num_geo: allowed number of geometry in the leaf
*/
bvh::bvh(std::vector <geometry*> scene_geometry, int num_geo) {
  //vectors for geo after split
  std::vector<geometry*> left_scene_geometry;
  std::vector<geometry*> right_scene_geometry;
  //index for spread
  int spread_index = random_int(0,3);
  point midpoint = get_midpoint(scene_geometry);
  //split the geometry
  for (int i = 0; i < scene_geometry.size(); i++) {
    if (scene_geometry[i]->get_bounding_box().centroid[spread_index] < midpoint[spread_index]) {
      left_scene_geometry.push_back(scene_geometry[i]);
    } else {
      right_scene_geometry.push_back(scene_geometry[i]);
    }
  }
  //create a new node or leaf
  if (left_scene_geometry.size() <= num_geo) {
    this->left = new hittables(left_scene_geometry);
  } else {
    this->left = new bvh(left_scene_geometry,num_geo);
  }
  if (right_scene_geometry.size() <= num_geo) {
    this->right = new hittables(right_scene_geometry);
  } else {
    this->right = new bvh(right_scene_geometry,num_geo);
  }
  //get the surrounding box
  aabb right_box = this->right->get_bounding_box();
  aabb left_box = this->left->get_bounding_box();
  this->box = left_box.surrounding_box(right_box);
}

void destroy_bvh_tree(geometry *node) {
  // for a given node
  // if that node-> left != NULL:
    //destroy_bvh_tree(node->left)
    // else:
    // delete node->left
  // if that node->right != NULL:
    //destroy_bvh_tree(node->right);
    // else
      // delete node->right;
  // delete node
}
//
bvh::~bvh() {

}

/*
BVH Hit Function
@param casted_ray: ray casted into the scene
@param t_min & t_max: max and min t values for parametric hit
@param rec: record to store a hit
*/
bool bvh::hit(ray &casted_ray, double t_min, double t_max, hit_record &rec) const {
  aabb bb = this->box;
  if (!bb.check_hit(casted_ray,t_min,t_max)) {
    return false;
  }
  bool hit_left = this->left->hit(casted_ray,t_min,t_max,rec);
  bool hit_right = this->right->hit(casted_ray,t_min,hit_left ? rec.t : t_max, rec);
  return hit_left || hit_right;
}

/*
Getting the Normal Vector of the Point on the Sphere
@param point_on_sphere: point to get normal vector at
@return: normal vector
*/
vec bvh::get_normal_vector(point &point_on_sphere) const {
  return vec();
}

//not used
material * bvh::get_material() const {
  return new material();
}

/*
Getting the bounding box of the sphere.
@return: the sphere's bounding box
*/
aabb bvh::get_bounding_box() const {
  return this->box;
}
