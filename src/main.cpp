#include "img.h"
#include "scene.h"
#include "camera.h"
#include "utils.h"

int main() {
    // scene
    std::vector<Sphere> spheres;
    auto sphere1 = Sphere(Point3(0, 0, -1.5), 0.6);
    auto sphere2 = Sphere(Point3(0, 100.5, 1), 100);
    const int ray_per_pixel = 30;

    spheres.push_back(sphere1);
    spheres.push_back(sphere2);
    auto scene = Scene(spheres);

    // image
    const auto ratio = 16.0 / 9.0;
    const int img_width = 400;
    const int img_height = static_cast<int>(img_width / ratio);
    Image img = Image(img_height, img_width);

    // camera
    Camera camera(ratio, 2.0, 1.0, Point3(0.0, 0.0, 0.0));

    for (int j = img_height - 1; j >= 0; j--) {
        for (int i = 0; i < img_width; i++) {
            auto current_color = Color();

            for (int k = 0; k < ray_per_pixel; k++) {
                auto step_w = (float(i) + generate_random_float(0.0, 1.0)) / (img_width - 1);
                auto step_h = (float(j) + generate_random_float(0.0, 1.0)) / (img_height - 1);
                auto ray = camera.create_ray(step_w, step_h);
                current_color = current_color + ray_cast(ray, scene, 2);
            }

            current_color = current_color / float(ray_per_pixel);
            auto proper_color = from_float_color_to_int(current_color);
            img.set_pixel(j, i, proper_color);
        }
    }

    img.SavePPM("test.ppm");
    return 0;
}