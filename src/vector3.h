#pragma once

#include <iostream>
#include <cmath>

struct Vector3 {
    Vector3(float x, float y, float z) : x(x), y(y), z(z) {}
    Vector3() : x(0), y(0), z(0) {}
    float x;
    float y;
    float z;

    Vector3 operator-(const float &l) const {
        return Vector3(this->x - l, this->y - l, this->z - l);
    }

    Vector3 operator-() const {
        return Vector3(-this->x, -this->y, -this->z);
    }

    Vector3 operator+=(const float &val) {
        this->x += val;
        this->y += val;
        this->z += val;
        return *this;
    }

    Vector3 operator*=(const float &l) {
        this->x *= l;
        this->y *= l;
        this->z *= l;
        return *this;
    }

    Vector3 operator/=(const double &val) {
        *this *= 1/val;
        return *this;
    }

    float length();
};

using Point3 = Vector3;
using Color = Vector3;

std::ostream& operator<<(std::ostream& os, Vector3 vector3);