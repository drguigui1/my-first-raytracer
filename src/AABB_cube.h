#pragma once

#include "ray.h"
#include "hit_point.h"
#include "material.h"

#include <stdlib.h>
#include <math.h>

class AABB_cube {
    public:
        AABB_cube(Point3 bottom_left, Point3 top_right, Material material);

        bool hit(const Ray &ray, float t_min, float t_max, Hit_point &hit_pts, int i, int j);

    private:
        // define the cube
        Point3 _bottom_left;
        Point3 _top_right;

        Material _material;
};