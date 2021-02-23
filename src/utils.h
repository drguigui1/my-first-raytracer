#pragma once

#include "ray.h"

// Utils functions for the ray tracer

Color ray_color_background(const Ray &ray);
Color from_float_color_to_int(Color c);