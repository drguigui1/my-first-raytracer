#include "vector3.h"

float Vector3::length() const {
    return std::sqrt(this->x * this->x + this->y * this->y + this->z * this->z);
}

bool Vector3::is_zeros() {
    auto l = 1e-8;
    if (abs(this->x) < l &&
        abs(this->y) < l &&
        abs(this->z) < l) {
        return true;
    }
    return false;
}

std::ostream& operator<<(std::ostream& os, const Vector3 &vector3) {
    os << "Vector3: \n";
    os << "x: " << vector3.x << "\ny: " << vector3.y << "\nz: " << vector3.z << '\n' ;
    return os;
}

Vector3 operator+(const Vector3 &v1, const Vector3 &v2) {
    return Vector3(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z);
}

Vector3 operator-(const Vector3 &v1, const Vector3 &v2) {
    return Vector3(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z);
}

Vector3 operator*(const Vector3 &v1, const Vector3 &v2) {
    return Vector3(v1.x * v2.x, v1.y * v2.y, v1.z * v2.z);
}

Vector3 operator*(const Vector3 &v, float val) {
    return Vector3(v.x * val, v.y * val, v.z * val);
}

Vector3 operator*(float val, const Vector3 &v) {
    return Vector3(v.x * val, v.y * val, v.z * val);
}

Vector3 operator/(const Vector3 &v, float val) {
    return v * (1.0 / val);
}

float dot_product(const Vector3 &v1, const Vector3 &v2) {
    return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

Vector3 cross_product(const Vector3 &v1, const Vector3 &v2) {
    return Vector3(v1.y * v2.z - v1.z * v2.y,
                   v1.z * v2.x - v1.x * v2.z,
                   v1.x * v2.y - v1.y * v2.x);
}

Vector3 unit_vector(const Vector3 &v) {
    return v / v.length(); 
}

Vector3 sqrt_vector(const Vector3 &v) {
    return Vector3(sqrt(v.x), sqrt(v.y), sqrt(v.z));
}

Vector3 reflect(const Vector3 &v1, const Vector3 &v2) {
    return v1 - 2.0 * dot_product(v1, v2) * v2;
}

Vector3 refract(const Vector3 &v1, const Vector3 &v2, float n1, float n2) {
    // dot product between v1 v2
    auto dot_p = dot_product(v1, v2);
    if (dot_p > 1.0)
        dot_p = 1.0;
    if (dot_p < -1.0)
        dot_p = -1.0;

    Vector3 normal = v2;
    if (dot_p < 0) { // means that the ray comes from inside the object
        dot_p = -dot_p;
        normal = -normal;
        std::swap(n1, n2);
    }
    auto ratio_n = n2 / n1;
    float k = 1 - ratio_n * ratio_n * (1 - dot_p * dot_p);
    if (k < 0) {
        return Vector3(1, 0, 0);
    }
    return v1 * ratio_n + v1 * (ratio_n * dot_p - sqrt(k));
}

// mult the vector by 9 element matrix (3x3 flatten)
// rotate point
Vector3 mult_by_mat(float* m, Vector3 &v) {
    float new_x = m[0] * v.x + m[1] * v.y + m[2] * v.z;
    float new_y = m[3] * v.x + m[4] * v.y + m[5] * v.z;
    float new_z = m[6] * v.x + m[7] * v.y + m[8] * v.z;
    return Vector3(new_x, new_y, new_z);
}
