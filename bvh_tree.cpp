#include "bvh_tree.h"
#include <unistd.h>

//bvh_tree Default Constructor
bvh_tree::bvh_tree() {}

/*
bvh_tree Specific Constructor
@param scene_geometry: vector of geometry
@param num_geo: allowed number of geometry in the leaf
*/
bvh_tree::bvh_tree(std::vector <geometry*> scene_geometry, int num_geo) {
  this->head = new bvh_node(scene_geometry,num_geo);
}

/*
prints the bvh_tree
@param node: current node for building tree
@param space: number of space for printing the tree
*/
void print_tree(geometry *node, int space) {
  if (node == NULL)
    return;

  space += 10;
  print_tree(node->get_right(),space);

  std::cout<<std::endl;
  for (int i = 10; i < space; i++) {
    std::cout<<" ";
  }
  node->get_bounding_box().centroid.print();
  print_tree(node->get_left(),space);
}

/*
Destroy the BVH tree
@param node: recursive destruction
*/
void bvh_tree::destroy_bvh_tree(geometry *node) {
  if (node == NULL)
    return;
  destroy_bvh_tree(node->get_right());
  destroy_bvh_tree(node->get_left());
  //if it is a leaf it is a hittables, so delete everythin in that
  if (node->is_leaf()) {
      for (int x = 0; x < node->get_geo().size(); x++) {
        delete node->get_geo()[x]->get_material();
        delete node->get_geo()[x];
      }
  }
  delete node;
}

//Destructor
bvh_tree::~bvh_tree() {
  destroy_bvh_tree(this->head);
}

/*
bvh_tree Hit Function
@param casted_ray: ray casted into the scene
@param t_min & t_max: max and min t values for parametric hit
@param rec: record to store a hit
*/
bool bvh_tree::hit(ray &casted_ray, double t_min, double t_max, hit_record &rec) const {
  return this->head->hit(casted_ray,t_min,t_max,rec);
}

//not used
vec bvh_tree::get_normal_vector(point &point_on_sphere) const {
  return vec();
}

//not used
material * bvh_tree::get_material() const {
  return new material();
}

//not used
aabb bvh_tree::get_bounding_box() const {
  return aabb();
}

//not used
geometry * bvh_tree::get_left() const {
  return NULL;
}

//not used
geometry * bvh_tree::get_right() const {
  return NULL;
}

//not used
bool bvh_tree::is_leaf() const {
  return false;
}

//not used
std::vector<geometry*> bvh_tree::get_geo() const {
  std::vector<geometry*> empty_list;
  return empty_list;
}
