#include "ray.h"

Ray::Ray(Point3 origin, Vector3 direction) : _origin(origin), _direction(direction) {}

Point3 Ray::ray_at(float t) const {
    return this->_origin + t * this->_direction;
}