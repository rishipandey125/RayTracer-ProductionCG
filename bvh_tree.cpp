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


void bvh_tree::destroy_bvh_tree(geometry *node) {
  if (node == NULL)
    return;
  destroy_bvh_tree(node->get_right());
  destroy_bvh_tree(node->get_left());
  if (node->is_leaf()) {
      for (int x = 0; x < node->get_geo().size(); x++) {
        delete node->get_geo()[x]->get_material();
        delete node->get_geo()[x];
      }
  }
  delete node;
}



bvh_tree::~bvh_tree() {
  // print_tree(this->head,0);
  destroy_bvh_tree(this->head);
}

/*
bvh_node Hit Function
@param casted_ray: ray casted into the scene
@param t_min & t_max: max and min t values for parametric hit
@param rec: record to store a hit
*/
bool bvh_tree::hit(ray &casted_ray, double t_min, double t_max, hit_record &rec) const {
  return this->head->hit(casted_ray,t_min,t_max,rec);
}

/*
Getting the Normal Vector of the Point on the Sphere
@param point_on_sphere: point to get normal vector at
@return: normal vector
*/
vec bvh_tree::get_normal_vector(point &point_on_sphere) const {
  return vec();
}

//not used
material * bvh_tree::get_material() const {
  return new material();
}

/*
Getting the bounding box of the sphere.
@return: the geo's bounding box
*/
aabb bvh_tree::get_bounding_box() const {
  return aabb();
}

geometry * bvh_tree::get_left() const {
  return NULL;
}

geometry * bvh_tree::get_right() const {
  return NULL;
}

bool bvh_tree::is_leaf() const {
  return false;
}

std::vector<geometry*> bvh_tree::get_geo() const {
  std::vector<geometry*> empty_list;
  return empty_list;
}
