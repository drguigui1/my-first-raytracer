#include "material.h"

Material::Material(float refract_idx, Vector3 color, float ns, std::tuple<float, float, float, float> albedo) {
    this->refraction_index = refract_idx;
    this->color = color;
    this->ns = ns;
    this->albedo_diffuse = std::get<0>(albedo);
    this->albedo_specular = std::get<1>(albedo);
    this->albedo_specular_color = std::get<2>(albedo);
    this->albedo_refraction = std::get<3>(albedo);
}