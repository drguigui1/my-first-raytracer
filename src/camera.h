#pragma once

#include "ray.h"

class Camera {
    public:
        Camera(float ratio, float window_height, float focal_length, Point3 origin) {
            this->_ratio = ratio;
            this->_window_height = window_height;
            this->_window_width = window_height * ratio;
            this->_focal_length = focal_length;
            this->_origin = origin;
            this->_horizontal = Vector3(_window_width, 0.0, 0.0);
            this->_vertical = Vector3(0.0, _window_height, 0.0);
            auto z_vec = Vector3(0.0, 0.0, focal_length);
            this->_lower_left_corner = origin - this->_horizontal / 2.0 - this->_vertical / 2.0 - z_vec;
        }

        Ray create_ray(float step_w, float step_h) {
            return Ray(this->_origin, this->_lower_left_corner + step_w * this->_horizontal + step_h * this->_vertical - this->_origin);
        }

    private:
        float _ratio;
        float _focal_length;
        float _window_height;
        float _window_width;
        Point3 _origin;
        Point3 _lower_left_corner;
        Vector3 _horizontal;
        Vector3 _vertical;
};