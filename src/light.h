#pragma once

#include "vector3.h"

class Light {
    public:
        Light(Point3 position, float intensity) : _position(position), _intensity(intensity) {}

        Point3 get_position() { return this->_position; }
        float get_intensity() { return this->_intensity; }

    private:
        Point3 _position;
        float _intensity;
};