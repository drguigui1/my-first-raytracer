#include "AABB_cube.h"

AABB_cube::AABB_cube(Point3 bottom_left, Point3 top_right, Material material)
    :
    _bottom_left(bottom_left),
    _top_right(top_right),
    _material(material)
{
}

float round_val(float val) {
    return round(val * 1000.0) / 1000.0;
}

bool AABB_cube::hit(const Ray &ray, float t_min, float t_max, Hit_point &hit_pts, int i, int j) {
    // compute tmin and tmax for the x component
    // check where the ray intersect planes made by x component of 'bottom_left' and 'top_right'
    // tmin: intersection with the bottom_left point x component plane
    auto tmin = (this->_bottom_left.x - ray.get_origin().x) / ray.get_direction().x;
    auto tmax = (this->_top_right.x - ray.get_origin().x) / ray.get_direction().x;

    // swap is usefull to be in the case where tmin is always smaller than tmax
    if (tmin > tmax) {
        std::swap(tmin, tmax);
    }

    auto tymin = (this->_bottom_left.y - ray.get_origin().y) / ray.get_direction().y;
    auto tymax = (this->_top_right.y - ray.get_origin().y) / ray.get_direction().y;

    if (tymin > tymax) {
        std::swap(tymin, tymax);
    }

    // The ray does not hit the cube
    if ((tmin > tymax) || (tymin > tmax)) {
        return false;
    }

    // tmin is outside of the cube
    if (tymin > tmin) {
        tmin = tymin;
    }
    if (tymax < tmax) {
        tmax = tymax;
    }

    auto tzmin = (this->_bottom_left.z - ray.get_origin().z) / ray.get_direction().z;
    auto tzmax = (this->_top_right.z - ray.get_origin().z) / ray.get_direction().z;

    if (tzmin > tzmax) {
        std::swap(tzmin, tzmax);
    }

    if ((tmin > tzmax) || (tzmin > tmax)) {
        return false;
    }

    if (tzmin > tmin) {
        tmin = tzmin;
    }

    if (tzmax < tmax) {
        tmax = tzmax;
    }

    if (tmin < t_min || tmin > t_max) {
        return false;
    }

    // set the hit points
    Point3 p = ray.ray_at(tmin);

    // Pts is on the x plane of the bottom left point
    if (round_val(p.x) == this->_bottom_left.x) {
        hit_pts.normal = Vector3(-1, 0, 0);
    } else if (round_val(p.x) == this->_top_right.x) {
        hit_pts.normal = Vector3(1, 0, 0);
    } else if (round_val(p.y) == this->_bottom_left.y) {
        hit_pts.normal = Vector3(0, -1, 0);
    } else if (round_val(p.y) == this->_top_right.y) {
        hit_pts.normal = Vector3(0, 1, 0);
    } else if (round_val(p.z) == this->_bottom_left.z) {
        hit_pts.normal = Vector3(0, 0, 1);
    } else if (round_val(p.z) == this->_top_right.z) {
        hit_pts.normal = Vector3(0, 0, -1);
    } else {
        std::cout << "ERROR" << '\n';
        std::cout << i << '\n';
        std::cout << j << '\n';
        exit(1);
    }

    tmin -= 1e-4;
    hit_pts.p = ray.ray_at(tmin);
    hit_pts.t = tmin;
    hit_pts.material = this->_material;
    hit_pts.hit_type = CUBE;

    return true;
}