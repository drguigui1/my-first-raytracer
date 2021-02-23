#pragma once

#include "volume.h"

class Sphere : public Volume {
    public:
        Sphere(Point3 center, float radius);
        Sphere();

        Point3 get_center() const { return this->_center; }
        float get_radius() const { return this->_radius; }

        virtual bool hit(const Ray &ray, float t_min, float t_max, Hit_point &hit_pts) const override;

    private:
        Point3 _center;
        float _radius;
};