#include "utils.h"

const float infinity = std::numeric_limits<float>::infinity();

double clamp(float val, float min, float max) {
    if (val < min) {
        return min;
    }
    if (val > max) {
        return max;
    }
    return val;
}

// Convert float color to int color (0-255)
Color from_float_color_to_int(Color c) {
    auto r = static_cast<int>(255.0 * clamp(c.x, 0.0, 1.0));
    auto g = static_cast<int>(255.0 * clamp(c.y, 0.0, 1.0));
    auto b = static_cast<int>(255.0 * clamp(c.z, 0.0, 1.0));

    return Color(r, g, b);
}

float generate_random_float(float inf, float sup) {
    static std::uniform_real_distribution<float> distribution(inf, sup);
    static std::mt19937 generator;
    return distribution(generator);
}

Vector3 random_in_unit_sphere() {
    while (true) {
        auto p = Vector3(generate_random_float(-1.0, 1.0), generate_random_float(-1.0, 1.0), generate_random_float(-1.0, 1.0));
        auto len = p.length();
        if (len * len >= 1) {
            continue;
        }
        return p;
    }
}

Color ray_cast(const Ray &ray, Scene scene, int depth) {
    if (depth == 0) {
        return Color(0, 0, 0);
    }
    auto spheres = scene.get_spheres();

    // if the ray hit the sphere
    auto hit_pts = Hit_point();
    if (spheres.size() != 0 && spheres[0].hit(ray, 0, infinity, hit_pts)) {
        Point3 pts_new_ray_dir = hit_pts.p + hit_pts.normal + random_in_unit_sphere();
        return 0.5 * ray_cast(Ray(hit_pts.p, pts_new_ray_dir - hit_pts.p), scene, depth - 1);
    }

    if (spheres.size() > 1 && spheres[1].hit(ray, 0, infinity, hit_pts)) {
        return Color(63.0 / 255.0, 200.0 / 255.0, 56.0 / 255.0);
    }

    Vector3 unit_dir = unit_vector(ray.get_direction());
    auto tmp = 0.5 * (-unit_dir.y + 1.0);
    return (1.0 - tmp) * Color(1.0, 1.0, 1.0) + tmp * Color(0.5, 0.7, 1.0);
}