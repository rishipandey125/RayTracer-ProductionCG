#ifndef AABB_H
#define AABB_H
//Header File for AABB Class
class aabb {
  public:
    //Constructors
    aabb();
    aabb(point &bottom_left, point &top_right);
    //member functions
    void operator=(const aabb &box);
    bool hit(ray &casted_ray, float &t_min, float &t_max);
    aabb surrounding_box(aabb &box);
    //Member Variables
    point min;
    point max;
    point centroid;
};
#endif
