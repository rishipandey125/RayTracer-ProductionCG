#include "box.h"
//Default Constructor
box::box() {}

box::box(point min, point max, material * geo_material) {
  //create aabb box
  this->bb = aabb(min,max);
  //create six rectangles
  float width = max.x - min.x;
  float height = max.y - min.y;
  float depth = max.z - min.z;
  //front facing
  this->sides.push_back(new plane(min,vec(min.x+width,min.y,min.z),vec(min.x,min.y+height,min.z),vec(min.x+width,min.y+height,min.z),geo_material));
  //right side
  this->sides.push_back(new plane(vec(min.x+width,min.y,min.z),vec(min.x+width,min.y+height,min.z),vec(min.x+width,min.y,min.z+depth),max,geo_material));
  //left side
  this->sides.push_back(new plane(min,vec(min.x,min.y+height,min.z),vec(min.x,min.y,min.z+depth),vec(min.x,min.y+height,min.z+depth),geo_material));
  //back side
  this->sides.push_back(new plane(vec(min.x,min.y,min.z+depth),vec(min.x,min.y+height,min.z+depth),vec(min.x+width,min.y,min.z+depth),max,geo_material));
  //top face
  this->sides.push_back(new plane(vec(min.x,min.y+height,min.z),vec(min.x+width,min.y+height,min.z),vec(min.x,min.y+height,min.z+depth),max,geo_material));
  //bottom face
  this->sides.push_back(new plane(min,vec(min.x+width,min.y,min.z),vec(min.x+width,min.y,min.z+depth),vec(min.x,min.y,min.z+depth),geo_material));
}

bool box::hit(ray &casted_ray, double t_min, double t_max, hit_record &rec) const {
  bool hit = false;
  for (int i = 0; i < this->sides.size(); i++) {
    //check for hit on each side
    if (this->sides[i]->hit(casted_ray,t_min,t_max,rec)) {
      hit = true;
      t_max = rec.t;
    }
  }
  return hit;
}

//unused
vec box::get_normal_vector(point &point_on_plane) const {
  return vec();
}

//unused most likely
material * box::get_material() const {
  return this->geo_material;
}
//bounding box of the box (just the same size of the box)
aabb box::bounding_box() const {
  return this->bb;
}
