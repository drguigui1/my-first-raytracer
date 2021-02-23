#include "scene.h"

Scene::Scene(Sphere s) {
    std::vector<Sphere> spheres;
    spheres.push_back(s);
    this->_spheres = spheres;
}