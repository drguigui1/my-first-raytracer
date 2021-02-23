#pragma once

#include "ray.h"

class Sphere {
    public:
        Sphere(Point3 center, float radius);
        Sphere();

        Point3 get_center() const { return this->_center; }
        float get_radius() const { return this->_radius; }

        bool hit_sphere(const Ray &ray);

    private:
        Point3 _center;
        float _radius;
};