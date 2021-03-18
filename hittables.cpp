#include "hittables.h"
hittables::hittables() {}

hittables::hittables(geometry * object) {
  this->add(object);
}

hittables::hittables(std::vector<geometry*> scene_geo) {
  this->geo = scene_geo;
}
void hittables::add(geometry * object) {
  this->geo.push_back(object);
}

bool hittables::hit(ray &casted_ray, double t_min, double t_max, hit_record &rec) const {
  bool hit = false;
  for (int i = 0; i < this->geo.size(); i++) {
    if (this->geo[i]->hit(casted_ray,t_min,t_max,rec)) {
      hit = true;
      t_max = rec.t;
    }
  }
  return hit;
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
