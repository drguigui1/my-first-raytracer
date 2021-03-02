#pragma once

#include <vector>

#include "light.h"
#include "sphere.h"
#include "plane.h"

class Scene {
    public:
        Scene(std::vector<Sphere> spheres, std::vector<Plane> planes, std::vector<Light> lights)
            :
            _spheres(spheres),
            _planes(planes),
            _lights(lights) {}
        Scene(Sphere s);

        std::vector<Sphere> get_spheres() { return  this->_spheres; }
        std::vector<Plane> get_planes() { return this-> _planes; }
        std::vector<Light> get_lights() { return this->_lights; }

    private:
        std::vector<Sphere> _spheres;
        std::vector<Plane> _planes;
        std::vector<Light> _lights;
};