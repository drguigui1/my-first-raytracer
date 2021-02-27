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

Vector3 random_ray_vector() {
    while (true) {
        auto p = Vector3(generate_random_float(-1.0, 1.0), generate_random_float(-1.0, 1.0), generate_random_float(-1.0, 1.0));
        auto len = p.length();
        if (len * len >= 1) {
            continue;
        }
        return unit_vector(p);
    }
}

// check if ray hits an object
// get the clothest
Hit_point hit_objects(Scene scene, const Ray &ray) {
    auto spheres = scene.get_spheres();

    float closest_hit_point = infinity;
    Hit_point final_hit;
    final_hit.has_hit = false;
    Hit_point temp_hit;

    for (int i = 0; i < spheres.size(); i++) {
        if (spheres[i].hit(ray, 0.001, closest_hit_point, temp_hit)) {
            closest_hit_point = temp_hit.t;
            final_hit = temp_hit;
            final_hit.has_hit = true;
            final_hit.sphere_idx = i;
        }
    }

    return final_hit;
}

Color compute_diffuse(Scene scene, Sphere sphere, Light light, Hit_point hit_pts) {
    // check if object between hit_pts and the light
    // if object -> the point must be dark
    auto L = Ray(hit_pts.p, light.get_position());
    auto hit_pts2 = hit_objects(scene, L);
    if (hit_pts2.has_hit) {
        return Color(); // return black
    }

    return sphere.get_diffuse_property() * sphere.get_color() * dot_product(hit_pts.normal, L.get_direction()) * light.get_intensity();
}

Color ray_cast(const Ray &ray, Scene scene, int depth) {
    if (depth == 0) {
        return Color(0, 0, 0);
    }
    auto spheres = scene.get_spheres();

    // if the ray hit the sphere
    auto hit_pts = hit_objects(scene, ray);
    if (hit_pts.has_hit) {
        //auto reflected_ray = reflect(unit_vector(ray.get_direction()), hit_pts.normal);
        // get diffuse component
        auto diffuse = compute_diffuse(scene, spheres[hit_pts.sphere_idx], scene.get_lights()[0], hit_pts);
        // get specular component
        // produce new ray TODO (according to material but for now random ray)
        // return  * 0.5 * ray_cast(Ray(hit_pts.p, reflected_ray), scene, depth - 1);
        return diffuse;
    }

    // background
    Vector3 unit_dir = unit_vector(ray.get_direction());
    auto tmp = 0.5 * (unit_dir.y + 1.0);
    return (1.0 - tmp) * Color(1.0, 1.0, 1.0) + tmp * Color(0.5, 0.7, 1.0);
}