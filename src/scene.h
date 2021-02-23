#pragma once

#include <vector>

#include "sphere.h"

class Scene {
    public:
        Scene(std::vector<Sphere> spheres) : _spheres(spheres) {}
        Scene(Sphere s);

        std::vector<Sphere> get_spheres() { return  this->_spheres; }

    private:
        std::vector<Sphere> _spheres;
};