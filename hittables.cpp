#include "hittables.h"
hittables::hittables() {}

hittables::hittables(geometry * object) {
  this->add(object);
}

void hittables::add(geometry * object) {
  this->geo.push_back(object);
}

float hittables::hit(ray &casted_ray) const {
  return 1.0;
}


//UNUSED
vec hittables::get_normal_vector(point &point_on_sphere) const {
  return vec();
}

//UNUSED
color hittables::get_base_color() const {
  return vec();
}


aabb hittables::bounding_box() const {
  aabb first_box = aabb();
  aabb output_box = aabb();
  for (int i = 0; i < (this->geo).size(); i++) {
    first_box = (this->geo)[i]->bounding_box();
    output_box = output_box.surrounding_box(first_box);
  }
  return output_box;
}
