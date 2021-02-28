#pragma once

#include <tuple>
#include "vector3.h"

class Material {
    public:
        Material(float refract_idx, Vector3 color, float ns, std::tuple<float, float, float, float> albedo);
        Material() {}
        float refraction_index;
        Vector3 color;
        float ns; // specular exponent
        float albedo_diffuse; // kd
        float albedo_specular; // ks
        float albedo_specular_color; // use to compute the reflected color
        float albedo_refraction;
};