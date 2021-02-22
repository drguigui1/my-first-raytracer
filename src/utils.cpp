#include "utils.h"

Color set_background(Ray &ray) {
    Vector3 unit_dir = unit_vector(ray.get_direction());
    auto tmp = 0.5 * (unit_dir.y + 1.0);
    return (1.0 - tmp) * Color(1.0, 1.0, 1.0) + tmp * Color(0.5, 0.7, 1.0);
}