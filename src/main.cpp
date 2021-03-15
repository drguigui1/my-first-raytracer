#include "img.h"
#include "utils.h"
#include "camera.h"

int main() {
    auto background_img_path = "sky_background_1000_800.ppm";

    // materials
    auto ground  = Material(1.0, Color(0.62, 0.49, 0.33), 10.0, std::tuple<float, float, float, float>(0.9,  0.1, 0.0, 0.0));
    auto ivory = Material(1.0, Color(0.81, 0.29, 0.17), 50.0, std::tuple<float, float, float, float>(0.6,  0.3, 0.1, 0.0));
    auto mirror = Material(1.0, Color(0.9, 0.9, 0.9), 1425.0, std::tuple<float, float, float, float>(0.0, 10.0, 0.8, 0.0));
    auto metal = Material(1.0, Color(0.15, 0.15, 0.15), 50.0, std::tuple<float, float, float, float>(0.8, 1.0, 0.2, 0.0));
    auto metal_deep = Material(1.0, Color(0.05, 0.05, 0.05), 500.0, std::tuple<float, float, float, float>(0.3, 5.0, 0.5, 0.0));
    auto mat_color_red = Material(1.0, Color(0.51, 0.14, 0.13), 5.0, std::tuple<float, float, float, float>(0.9, 0.1, 0.1, 0.0));
    auto mat_color_blue = Material(1.0, Color(0.31, 0.8, 0.82), 5.0, std::tuple<float, float, float, float>(0.9, 0.1, 0.1, 0.0));
    auto refract = Material(1.5, Color(0.31, 0.8, 0.82), 125.0, std::tuple<float, float, float, float>(0.0, 0.5, 0.1, 0.8));

    // scene
    std::vector<Sphere> spheres;
    // //spheres.push_back(Sphere(Point3(0.0, -0.3, -3.8), 0.6, mat_color_red));
    // spheres.push_back(Sphere(Point3(1.5, -0.25, -3.8), 0.6, mirror));
    // spheres.push_back(Sphere(Point3(-1.5, -0.25, -3.8), 0.6, metal));

    // // spheres.push_back(Sphere(Point3(-0.2, -0.6, -1.9), 0.3, ground));
    // spheres.push_back(Sphere(Point3(-1.3, -0.5, -1.9), 0.3, mat_color_blue));
    // // spheres.push_back(Sphere(Point3(1.2, -0.6, -1.9), 0.3, ivory));

    std::vector<Plane> planes;
    auto range_x = std::tuple<float, float>{-3.5, 3.5};
    auto range_y = std::tuple<float, float>{-1.0, 0.0}; // useless in this case
    auto range_z = std::tuple<float, float>{-6.0, -1.0};
    planes.push_back(Plane(Point3(0.0, -0.9, -3.5), Vector3(0.0, 1.0, 0.0), ground, range_x, range_y, range_z));

    std::vector<AABB_cube> aabb_cubes;
    // auto llp = Point3(0.7, -0.8, -1.7);
    // auto urp = Point3(1.5, 0.0, -2.5);
    // aabb_cubes.push_back(AABB_cube(llp, urp, metal_deep));

    // auto llp2 = Point3(-0.3, -0.8, -3.1);
    // auto urp2 = Point3(0.3, -0.2, -3.7);
    // aabb_cubes.push_back(AABB_cube(llp2, urp2, mat_color_red));

    std::vector<Triangle> triangles;
    auto p1 = Point3(0.0, 0.0, -3.0);
    auto p2 = Point3(0.0, 2.0, -3.0);
    auto p3 = Point3(2.0, 0.0, -3.0);
    auto tr = Triangle(p1, p2, p3, mat_color_blue);
    triangles.push_back(tr);

    std::vector<Light> lights;
    lights.push_back(Light(Point3(-2.2, 3.5, -1.0), 0.9));
    //lights.push_back(Light(Point3(0.0, 3.5, 0.0), 0.9));
    lights.push_back(Light(Point3(5.0, 3.5, -1.0), 0.9));

    auto scene = Scene(spheres, planes, aabb_cubes, triangles, lights, background_img_path);

    // image
    const int img_width = 600;
    const int img_height = 500;
    const int aspect_ratio = float(img_width) / float(img_height);
    Image img = Image(img_height, img_width);

    // camera
    float field_of_view = M_PI / 2;
    Camera camera(aspect_ratio, field_of_view, img_width, img_height, Point3(0.0, 2.0, 0.0), -M_PI / 4.0, 0.0, 0.0);

    // number of ray per pixel
    float n_rays_per_pixel = 10;

    std::cout << "height: " << img_height << '\n';
    for (int j = 0; j < img_height; j++) {
        if (j % 100 == 0)
            std::cout << j << '\n';
        for (int i = 0; i < img_width; i++) {
            auto current_color = Color();
            for (int k = 0; k < n_rays_per_pixel; k++) {
                auto ray = camera.create_ray(float(i) + generate_random_float(0.0, 1.0), float(j) + generate_random_float(0.0, 1.0));
                current_color = current_color + ray_cast(ray, scene, 5, j, i);
            }
            current_color = current_color / n_rays_per_pixel;
            current_color = sqrt_vector(current_color); // gamma correction (1/2)
            auto proper_color = from_float_color_to_int(current_color);
            img.set_pixel(j, i, proper_color);
        }
    }
    std::cout << '\n';

    img.SavePPM("test.ppm");
    std::cout << scene.get_background_rgb().get_height() << '\n';
    std::cout << scene.get_background_rgb().get_width() << '\n';
    return 0;
}