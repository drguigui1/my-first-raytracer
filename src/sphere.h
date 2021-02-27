#pragma once

#include <memory>

#include "volume.h"

class Sphere : public Volume {
    public:
        Sphere(Point3 center, float radius, Color color, float diffuse, float reflect);
        Sphere();

        Point3 get_center() const { return this->_center; }
        float get_radius() const { return this->_radius; }
        Color get_color() const { return this->_color; }
        float get_diffuse_property() const { return this->_diffuse_property; }
        float get_reflect_property() const { return this->_reflect_property; }

        virtual bool hit(const Ray &ray, float t_min, float t_max, Hit_point &hit_pts) const override;

    private:
        Point3 _center;
        float _radius;
        Color _color;
        float _diffuse_property;
        float _reflect_property;
};