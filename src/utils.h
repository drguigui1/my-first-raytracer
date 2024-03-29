#pragma once

#include <random>

#include "ray.h"
#include "scene.h"

// Utils functions for the ray tracer

Color from_float_color_to_int(Color c);
Color ray_cast(const Ray &ray, Scene scene, int depth, int i, int j);
float generate_random_float(float inf, float sup);
Vector3 random_ray_vector();