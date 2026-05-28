#ifndef HITTABLE_H
#define HITTABLE_H

#include "ray.h"

// A simple structure to hold the "results" of a hit
struct hit_record {
    point3 p;      // Where did it hit?
    vec3 normal;   // What is the surface normal?
    double t;      // At what distance?
};

class hittable {
  public:
    virtual ~hittable() = default;

    // Pure virtual function: Every object must implement its own ray-intersection math
    // t_min and t_max define the "valid" range for hits (to avoid hitting objects behind the camera)
    virtual bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const = 0;
};

#endif