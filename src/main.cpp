#include "img.h"
#include "ray.h"
#include "utils.h"

int main() {
    // image
    const auto aspect_ratio = 16.0 / 9.0;
    const int img_width = 400;
    const int img_height = static_cast<int>(img_width / aspect_ratio);
    Image img = Image(img_height, img_width);

    // camera
    auto focal_length = 1.0;
    auto window_height = 2.0;
    auto window_width = aspect_ratio * window_height;
    auto origin = Point3(0, 0, 0);

    auto horizontal = Vector3(window_width, 0, 0);

    auto vertical = Vector3(0, window_height, 0);
    auto z_vec = Vector3(0, 0, focal_length);
    auto lower_left_corner = origin - horizontal / 2.0 - vertical / 2.0 - z_vec;

    for (int j = img_height - 1; j >= 0; j--) {
        for (int i = 0; i < img_width; i++) {
            auto step_w = float(i) / (img_width - 1);
            auto step_h = float(j) / (img_height - 1);
            auto ray = Ray(origin, lower_left_corner + step_w * horizontal + step_h * vertical - origin);
            Color c = ray_color_background(ray);
            auto proper_c = from_float_color_to_int(c);
            img.set_pixel(j, i, proper_c);
        }
    }

    img.SavePPM("test.ppm");
    return 0;
}