#ifndef AABB_H
#define AABB_H
//Header File for AABB Class
class aabb {
  public:
    //Constructors
    aabb();
    aabb(point a, point b);
    //Member Functions
    void operator=(const aabb &box);
    bool check_hit(ray &casted_ray, float t_min, float t_max);
    aabb surrounding_box(aabb &box);
    //Member Variables
    point minimum;
    point maximum;
    point centroid;

};

#endif
