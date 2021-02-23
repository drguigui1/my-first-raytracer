#pragma once

#include "ray.h"
#include "hit_point.h"

class Volume {
    public:
        virtual bool hit(const Ray &r, float t_min, float t_max, Hit_point &hit_pts) const = 0;
};