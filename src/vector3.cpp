#include "vector3.h"

float Vector3::length() {
    return std::sqrt(this->x * this->x + this->y * this->y + this->z * this->z);
}

std::ostream& operator<<(std::ostream& os, Vector3 vector3) {
    os << "Vector3: \n";
    os << "x: " << vector3.x << "\ny: " << vector3.y << "\nz: " << vector3.z << '\n' ;
    return os;
}

Vector3 operator+(Vector3 v1, Vector3 v2) {
    return Vector3(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z);
}

Vector3 operator-(Vector3 v1, Vector3 v2) {
    return Vector3(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z);
}

Vector3 operator*(Vector3 v1, Vector3 v2) {
    return Vector3(v1.x * v2.x, v1.y * v2.y, v1.z * v2.z);
}

Vector3 operator*(Vector3 v, float val) {
    return Vector3(v.x * val, v.y * val, v.z * val);
}

Vector3 operator*(float val, Vector3 v) {
    return Vector3(v.x * val, v.y * val, v.z * val);
}

Vector3 operator/(Vector3 v, float val) {
    return v * 1 / val;
}

float dot_product(Vector3 v1, Vector3 v2) {
    return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

Vector3 cross_product(Vector3 v1, Vector3 v2) {
    return Vector3(v1.y * v2.z - v1.z * v2.y,
                   v1.z * v2.x - v1.x * v2.z,
                   v1.x * v2.y - v1.y * v2.x);
}

Vector3 unit_vector(Vector3 v) {
    return v / 3; 
}