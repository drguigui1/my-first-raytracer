#include "utils.h"

Color ray_color_background(const Ray &ray) {
    Vector3 unit_dir = unit_vector(ray.get_direction());
    auto tmp = 0.5 * (-unit_dir.y + 1.0);
    return (1.0 - tmp) * Color(1.0, 1.0, 1.0) + tmp * Color(0.5, 0.7, 1.0);
}

// Convert float color to int color (0-255)
Color from_float_color_to_int(Color c) {
    auto r = static_cast<int>(255.999 * c.x);
    auto g = static_cast<int>(255.999 * c.y);
    auto b = static_cast<int>(255.999 * c.z);

    return Color(r, g, b);
}