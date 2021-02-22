#pragma once

#include <iostream>

struct Vector3 {
    Vector3(float x, float y, float z) : x(x), y(y), z(z) {}
    Vector3() : x(0), y(0), z(0) {}
    float x;
    float y;
    float z;

    Vector3 operator+(const float &l) const {
        auto new_x = this->x + l;
        auto new_y = this->y + l;
        auto new_z = this->z + l;
        return Vector3(new_x, new_y, new_z);
    }

    Vector3 operator-(const float &l) const {
        auto new_x = this->x - l;
        auto new_y = this->y - l;
        auto new_z = this->z - l;
        return Vector3(new_x, new_y, new_z);
    }

    Vector3 operator*(const float &l) const {
        auto new_x = this->x * l;
        auto new_y = this->y * l;
        auto new_z = this->z * l;
        return Vector3(new_x, new_y, new_z);
    }
};

std::ostream& operator<<(std::ostream& os, Vector3 vector3) {
    os << "Vector3: \n";
    os << "x: " << vector3.x << "\ny: " << vector3.y << "\nz: " << vector3.z << '\n' ;
    return os;
}