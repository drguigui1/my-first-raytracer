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

float max_float(float a, float b) {
    if (a > b) {
        return a;
    }
    return b;
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
    Hit_point hit_pts = Hit_point();
    hit_pts.has_hit = false;

    for (int i = 0; i < spheres.size(); i++) {
        if (spheres[i].hit(ray, 0.001, closest_hit_point, hit_pts)) {
            hit_pts.sphere_idx = i; // maybe remove
            hit_pts.has_hit = true;
        }
    }
    return hit_pts;
}

// Color compute_intensity(Scene &scene, Hit_point &hit_pts, const Ray &input_ray, Ray &reflected_ray) {
//     // reflected dir
//     Vector3 reflected_dir = unit_vector(reflect(input_ray.get_direction(), hit_pts.normal));
//     Point3 reflected_origin = dot(reflect_dir, hit_pts.normal) < 0 ? hit_pts.p - hit_pts.normal * 1e-3 : hit_pts.p - hit_pts.normal * 1e-3;
//     // TODO reflraction

//     // recursive calls

//     Color intensity = Color();
//     for (int i = 0; i < lights.size(); i++) {
//         auto L = Ray(hit_pts.p, unit_vector(lights[i].get_position() - hit_pts.p));
//         auto hit_pts2 = hit_objects(scene, L);
//         if (hit_pts2.has_hit) {
//             continue;
//         }

//         // compute diffuse component
//         Color diffuse = sphere.get_diffuse_property() * sphere.get_color() * dot_product(hit_pts.normal, L.get_direction()) * lights[i].get_intensity();
//         // compute specular component
//         auto ns = sphere.get_ns();
//         auto reflect_vec = reflect(input_ray.get_direction(), hit_pts.normal);
//         reflect_vec = unit_vector(reflect_vec);
//         reflected_ray = Ray(hit_pts.p, reflect_vec);
//         //Color specular = sphere.get_reflect_property() * lights[i].get_intensity() * powf(dot_product(reflect_vec, L.get_direction()), ns);
//         //intensity = intensity + diffuse + specular;
//         intensity = intensity + diffuse;
//     }

//     return intensity;
// }

Color ray_cast(const Ray &ray, Scene scene, int depth) {
    if (depth == 0) {
        return Color(0.2, 0.7, 0.8);
    }

    auto spheres = scene.get_spheres();
    auto hit_pts = hit_objects(scene, ray);

    if (!hit_pts.has_hit) {
        // background
        Vector3 unit_dir = unit_vector(ray.get_direction());
        auto tmp = 0.5 * (unit_dir.y + 1.0);
        return (1.0 - tmp) * Color(1.0, 1.0, 1.0) + tmp * Color(0.5, 0.7, 1.0);
    }

    // reflected dir
    Vector3 reflected_dir = unit_vector(reflect(ray.get_direction(), hit_pts.normal));
    Point3 reflected_origin = dot_product(reflected_dir, hit_pts.normal) < 0 ? hit_pts.p - hit_pts.normal * 1e-3 : hit_pts.p - hit_pts.normal * 1e-3;
    // TODO refraction

    // recursive calls
    Color reflected_color = ray_cast(Ray(reflected_origin, reflected_dir), scene, depth - 1);
    // TODO recursive call for refraction

    // compute diffuse / specular and refraction components
    float diffuse_intensity_tmp = 0;
    float specular_intensity_tmp = 0;

    auto lights = scene.get_lights();
    for (int i = 0; i < lights.size(); ++i) {
        Vector3 light_dir = unit_vector(lights[i].get_position() - hit_pts.p);

        // check if point is in shadow of this light
        auto shadow_pts = dot_product(light_dir, hit_pts.normal) < 0 ? hit_pts.p - hit_pts.normal * 1e-3 : hit_pts.p - hit_pts.normal * 1e-3;
        auto hit_pts_shadow = hit_objects(scene, Ray(shadow_pts, light_dir));
        if (hit_pts_shadow.has_hit) {
            continue;
        }

        auto light_intensity = lights[i].get_intensity();
        diffuse_intensity_tmp += light_intensity * max_float(0.0, dot_product(light_dir, hit_pts.normal));

        auto reflected_ray = -reflect(-light_dir, hit_pts.normal);
        specular_intensity_tmp += light_intensity * powf(max_float(0.0, dot_product(reflected_ray, ray.get_direction())), hit_pts.material.ns);
    }

    auto diffuse_intensity =  hit_pts.material.color * diffuse_intensity_tmp * hit_pts.material.albedo_diffuse;
    auto specular_intensity = specular_intensity_tmp * hit_pts.material.albedo_specular;
    auto reflected_c = reflected_color * hit_pts.material.albedo_specular_color;
    // TODO refraction

    return diffuse_intensity + Vector3(1.0, 1.0, 1.0) * specular_intensity + reflected_c;
}