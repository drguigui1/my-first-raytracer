#pragma once

#include <math.h>
#include "ray.h"

class Camera {
    public:
        Camera(float aspect_ratio, float field_of_view, int img_width, int img_height, Point3 origin, float theta_x, float theta_y, float theta_z) {
            this->_aspect_ratio = aspect_ratio;
            this->_origin = origin;
            this->_field_of_view = field_of_view;
            this->_img_width = img_width;
            this->_img_height = img_height;

            // build the rotation matrix
            this->_rotation_x = new float[9];
            this->_rotation_y = new float[9];
            this->_rotation_z = new float[9];

            float mat_x_rotation[9] = {1.0, 0.0, 0.0, 0.0, cos(theta_x), -sin(theta_x), 0.0, sin(theta_x), cos(theta_x)};
            float mat_y_rotation[9] = {cos(theta_y), 0.0, sin(theta_y), 0.0, 1.0, 0.0, -sin(theta_y), 0.0, cos(theta_y)};
            float mat_z_rotation[9] = {cos(theta_z), -sin(theta_z), 0.0, sin(theta_z), cos(theta_z), 0.0, 0.0, 0.0, 1.0};

            for (int i = 0; i < 9; i++) {
                this->_rotation_x[i] = mat_x_rotation[i];
                this->_rotation_y[i] = mat_y_rotation[i];
                this->_rotation_z[i] = mat_z_rotation[i];
            }
        }

        ~Camera() {
            delete[] this->_rotation_x;
            delete[] this->_rotation_y;
            delete[] this->_rotation_z;
        }

        // Convert the pixel point from raster point to world point
        // Then create the ray
        // i : pixel column wise
        // j : pixel row wise
        Ray create_ray(float i, float j) {
            float px = (2.0 * (i + 0.5) / (float)this->_img_width - 1.0) * tan(this->_field_of_view * 0.5); 
            float py = (1.0 - 2.0 * (j + 0.5) / (float)this->_img_height) * tan(this->_field_of_view * 0.5) * 1.0 / this->_aspect_ratio;

            float pz = -1.0;
            auto ray_dir = Vector3(px, py, pz);
            ray_dir = unit_vector(ray_dir);

            // rotate the vector if necessary
            // rotation on x / y / z
            ray_dir = mult_by_mat(this->_rotation_x, ray_dir);
            ray_dir = mult_by_mat(this->_rotation_y, ray_dir);
            ray_dir = mult_by_mat(this->_rotation_z, ray_dir);

            return Ray(this->_origin, ray_dir);
        }

        // Ray create_ray(float step_w, float step_h) {
        //     return Ray(this->_origin, this->_lower_left_corner + step_w * this->_horizontal + step_h * this->_vertical - this->_origin);
        // }

    private:
        float _aspect_ratio;
        float _field_of_view; // must be converted in radian
        int _img_width;
        int _img_height;
        Point3 _origin;
        float* _rotation_x; // size 9
        float* _rotation_y; // size 9
        float* _rotation_z; // size 9
};