#pragma once

#include <tuple>

#include "ray.h"
#include "hit_point.h"
#include "material.h"

class Plane {
    public:
        Plane(Point3 p0,
              Vector3 normal,
              Material material,
              std::tuple<float, float> range_x,
              std::tuple<float, float> range_y,
              std::tuple<float, float> range_z);

        bool is_in_range(Point3 p);
        bool hit(const Ray &ray, float t_min, float t_max, Hit_point &hit_pts);
    private:
        Point3 _p0;  // Center of the plane
        Vector3 _normal; // Normal vector of the plane
        std::tuple<float, float> _range_x;
        std::tuple<float, float> _range_y;
        std::tuple<float, float> _range_z;
        Material _material;
};