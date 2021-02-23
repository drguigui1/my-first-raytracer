#include "sphere.h"

Sphere::Sphere(Point3 center, float radius) : _center(center), _radius(radius) {}

Sphere::Sphere() : _center(Point3(0, 0, 0)), _radius(1) {}


/*
** Eq of the ray: P(t) = A + tb
** with A:origin and b:direction
**
** Eq of the sphere: (P-C)(P-C) = r^2
** with: P=(x,y,z) , C=center and r=radius
**
** So intersection between sphere and ray:
** t^2 * b.b + 2t*b.(A-C) + (A-C).(A-C) - r^2 = 0
*/
bool Sphere::hit_sphere(const Ray &ray) {
    auto diff = ray.get_origin() - this->_center;

    // compute a, b, c from ax^2 + bx + c = 0
    auto a = dot_product(ray.get_direction(), ray.get_direction());
    auto b = dot_product(2.0 * ray.get_direction(), diff);
    auto c = dot_product(diff, diff) - this->_radius * this->_radius;

    // compute delta
    auto delta = b * b - 4.0 * a * c;
    return delta >= 0;
}