#pragma once

#include <iostream>

struct Point3 {
    Point3(float x, float y, float z) : x(x), y(y), z(z) {}
    Point3() : x(0), y(0), z(0) {} 
    float x;
    float y;
    float z;

    Point3 operator+(const float &l) const {
        auto new_x = this->x + l;
        auto new_y = this->y + l;
        auto new_z = this->z + l;
        return Point3(new_x, new_y, new_z);
    }

    Point3 operator-(const float &l) const {
        auto new_x = this->x - l;
        auto new_y = this->y - l;
        auto new_z = this->z - l;
        return Point3(new_x, new_y, new_z);
    }

    Point3 operator*(const float &l) const {
        auto new_x = this->x * l;
        auto new_y = this->y * l;
        auto new_z = this->z * l;
        return Point3(new_x, new_y, new_z);
    }
};

std::ostream& operator<<(std::ostream& os, Point3 point3) {
    os << "Point3: \n";
    os << "x: " << point3.x << "\nY: " << point3.y << "\nz: " << point3.z << '\n';
    return os;
}