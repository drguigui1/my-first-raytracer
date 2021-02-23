#pragma once

#include "ray.h"
#include "scene.h"

// Utils functions for the ray tracer

Color from_float_color_to_int(Color c);
Color ray_cast(const Ray &ray, Scene scene);