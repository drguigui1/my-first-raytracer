#pragma once

#include <memory>

#include "ray.h"
#include "hit_point.h"
#include "material.h"

class Sphere {
    public:
        Sphere(Point3 center, float radius, Material material);

        Point3 get_center() const { return this->_center; }
        float get_radius() const { return this->_radius; }
        Material get_material() const { return this->_material; }

        bool hit(const Ray &ray, float t_min, float t_max, Hit_point &hit_pts);

    private:
        Point3 _center;
        float _radius;
        Material _material;
};