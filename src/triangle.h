#pragma once

#include "ray.h"
#include "hit_point.h"
#include "material.h"

class Triangle {
    public:
        Triangle(Point3 p0, Point3 p1, Point3 p2, Material material);

        bool hit(const Ray &ray, float t_min, float t_max, Hit_point &hit_pts,
                int i, int j);
    private:
        Point3 _p0;
        Point3 _p1;
        Point3 _p2;

        Vector3 _edge0; // p1 - p0
        Vector3 _edge1; // p2 - p1
        Vector3 _edge2; // p0 - p2

        Vector3 _normal;
        Material _material;
};
