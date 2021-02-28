#pragma once

#include <iostream>
#include <cmath>

struct Vector3 {
    Vector3(float x, float y, float z) : x(x), y(y), z(z) {}
    Vector3() : x(0), y(0), z(0) {}

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

    float length() const;
    bool is_zeros();

    float x;
    float y;
    float z;
};

using Point3 = Vector3;
using Color = Vector3;

std::ostream& operator<<(std::ostream& os, const Vector3 &vector3);
Vector3 operator+(const Vector3 &v1, const Vector3 &v2);
Vector3 operator-(const Vector3 &v1, const Vector3 &v2);
Vector3 operator*(const Vector3 &v1, const Vector3 &v2);
Vector3 operator*(const Vector3 &v, float val);
Vector3 operator*(float val, const Vector3 &v);
Vector3 operator/(const Vector3 &v, float val);
float dot_product(const Vector3 &v1, const Vector3 &v2);
Vector3 cross_product(const Vector3 &v1, const Vector3 &v2);
Vector3 unit_vector(const Vector3 &v);
Vector3 sqrt_vector(const Vector3 &v);

// v1: input direction vector ray
// v2: normal vector
Vector3 reflect(const Vector3 &v1, const Vector3 &v2);

Vector3 mult_by_mat(float* m, Vector3 &v);