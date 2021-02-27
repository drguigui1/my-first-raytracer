#pragma once

#include <vector>

#include "light.h"
#include "sphere.h"

class Scene {
    public:
        Scene(std::vector<Sphere> spheres, std::vector<Light> lights) : _spheres(spheres), _lights(lights) {}
        Scene(Sphere s);

        std::vector<Sphere> get_spheres() { return  this->_spheres; }
        std::vector<Light> get_lights() { return this->_lights; }

    private:
        std::vector<Sphere> _spheres;
        std::vector<Light> _lights;
};