#pragma once

#include "vector3.h"

class Ray {
    public:
        Ray() {}
        Ray(Point3 origin, Vector3 direction);

        Point3 get_origin() const { return this->_origin; }
        Vector3 get_direction() const { return this->_direction; }

        Point3 ray_at(float t);

    private:
        Point3 _origin;
        Vector3 _direction;
};