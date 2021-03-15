#pragma once

#include "material.h"

enum Hit_type {
    SPHERE,
    PLANE,
    CUBE
};

struct Hit_point {
    Hit_point() {}
    Point3 p;
    Vector3 normal;
    float t;
    bool has_hit;
    Material material;
    Hit_type hit_type;
};