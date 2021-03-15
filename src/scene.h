#pragma once

#include <vector>

#include "light.h"
#include "sphere.h"
#include "plane.h"
#include "AABB_cube.h"
#include "triangle.h"
#include "img_io.h"

class Scene {
    public:
        Scene(std::vector<Sphere> spheres,
              std::vector<Plane> planes,
              std::vector<AABB_cube> aabb_cube,
              std::vector<Triangle> triangles,
              std::vector<Light> lights,
              const char* background)
            :
            _spheres(spheres),
            _planes(planes),
            _aabb_cubes(aabb_cube),
            _triangles(triangles),
            _lights(lights) {}
            //_background_img(load_image(background)) {}
        Scene(Sphere s);

        std::vector<Sphere> get_spheres() { return  this->_spheres; }
        std::vector<Plane> get_planes() { return this->_planes; }
        std::vector<AABB_cube> get_aabb_cubes() { return this->_aabb_cubes; }
        std::vector<Triangle> get_triangles() { return this->_triangles; }
        std::vector<Light> get_lights() { return this->_lights; }
        rgb24_image get_background_rgb() { return this->_background_img; }

    private:
        std::vector<Sphere> _spheres;
        std::vector<Plane> _planes;
        std::vector<AABB_cube> _aabb_cubes;
        std::vector<Triangle> _triangles;
        std::vector<Light> _lights;
        rgb24_image _background_img;

};
