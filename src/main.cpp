#include "img.h"
#include "scene.h"
#include "utils.h"
#include "camera.h"

int main() {
    // scene
    std::vector<Sphere> spheres;
    spheres.push_back(Sphere(Point3(0, -100.5, 1.0), 100, Color(184.0 / 255.0, 133.0 / 255.0, 51.0 / 255.0), 1.0, 0.0));
    spheres.push_back(Sphere(Point3(1.3, 0.0, -3.5), 0.5, Color(184.0 / 255.0, 51.0 / 255.0, 178.0 / 255.0), 0.3, 0.0));
    spheres.push_back(Sphere(Point3(-1.2, 0.0, -3), 0.5, Color(184.0 / 255.0, 51.0 / 255.0, 77.0 / 255.0), 0.7, 0.0));
    spheres.push_back(Sphere(Point3(0.0, 0.0, -3.3), 0.5, Color(185.0 / 255.0, 198.0 / 255.0, 104.0 / 255.0), 0.8, 0.0));
    std::vector<Light> lights;
    lights.push_back(Light(Point3(0.0, 2.0, -0.3), 0.4));
    auto scene = Scene(spheres, lights);

    const int ray_per_pixel = 30;

    // image
    const int img_width = 640;
    const int img_height = 480;
    const int aspect_ratio = float(img_width) / float(img_height);
    Image img = Image(img_height, img_width);

    // camera
    float field_of_view = M_PI / 2; // pi / 2
    Camera camera(aspect_ratio, field_of_view, img_width, img_height, Point3(0.0, 2.0, -1.0), -M_PI / 4.0, 0.0, 0.0);

    // number of ray per pixel
    float n_rays_per_pixel = 20;

    for (int j = 0; j < img_height; j++) {
        for (int i = 0; i < img_width; i++) {
            auto current_color = Color();
            for (int k = 0; k < n_rays_per_pixel; k++) {
                auto ray = camera.create_ray(float(i) + generate_random_float(0.0, 1.0), float(j) + generate_random_float(0.0, 1.0));
                current_color = current_color + ray_cast(ray, scene, 3);
            }
            current_color = current_color / n_rays_per_pixel;
            current_color = sqrt_vector(current_color); // gamma correction (1/2)
            auto proper_color = from_float_color_to_int(current_color);
            img.set_pixel(j, i, proper_color);
        }
    }

    img.SavePPM("test.ppm");
    return 0;
}