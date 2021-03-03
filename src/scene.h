#pragma once

#include <vector>

#include "light.h"
#include "sphere.h"
#include "plane.h"
#include "img_io.h"

class Scene {
    public:
        Scene(std::vector<Sphere> spheres, std::vector<Plane> planes, std::vector<Light> lights, const char* background)
            :
            _spheres(spheres),
            _planes(planes),
            _lights(lights),
            _background_img(load_image(background)) {}
        Scene(Sphere s);

        std::vector<Sphere> get_spheres() { return  this->_spheres; }
        std::vector<Plane> get_planes() { return this-> _planes; }
        std::vector<Light> get_lights() { return this->_lights; }
        rgb24_image get_background_rgb() { return this->_background_img; }

    private:
        std::vector<Sphere> _spheres;
        std::vector<Plane> _planes;
        std::vector<Light> _lights;
        rgb24_image _background_img;

};