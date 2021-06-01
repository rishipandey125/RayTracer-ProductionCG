#include "hittables.h"

//Default Constructor
hittables::hittables() {}

//Specific Constructor for Hittables with a single Geo
hittables::hittables(geometry * object) {
  this->add(object);
}

//constructor for a scene of geometry
hittables::hittables(std::vector<geometry*> scene_geo) {
  this->geo = scene_geo;
}

//destructor for deleting the scene geometry and materials on the heap to prevent mem leaks
hittables::~hittables() {
  for (int x = 0; x < this->geo.size(); x++) {
    delete this->geo[x]->get_material();
    delete this->geo[x];
  }
}
//adding a geo to the scene
void hittables::add(geometry * object) {
  this->geo.push_back(object);
}

/*
Hittables Hit Function
@param casted_ray: ray casted into the scene
@param t_min & t_max: max and min t values for parametric hit
@param rec: record to store a hit
*/
bool hittables::hit(ray &casted_ray, double t_min, double t_max, hit_record &rec) const {
  bool hit = false;
  for (int i = 0; i < this->geo.size(); i++) {
    //check hit for each geo
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
material * hittables::get_material() const {
  return new material();
}
