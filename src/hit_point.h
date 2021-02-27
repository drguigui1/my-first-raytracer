#pragma once

#include "vector3.h"

struct Hit_point {
    Hit_point() {}
    Point3 p;
    Vector3 normal;
    float t;
    int sphere_idx;
    bool has_hit;
};