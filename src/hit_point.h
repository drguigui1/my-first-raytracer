#pragma once

#include "material.h"

struct Hit_point {
    Hit_point() {}
    Point3 p;
    Vector3 normal;
    float t;
    bool has_hit;
    Material material;
};