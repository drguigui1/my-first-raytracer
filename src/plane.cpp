#include "plane.h"

Plane::Plane(Point3 p0,
             Vector3 normal,
             Material material,
             std::tuple<float, float> range_x,
             std::tuple<float, float> range_y,
             std::tuple<float, float> range_z)
    :
    _p0(p0),
    _normal(normal),
    _material(material),
    _range_x(range_x),
    _range_y(range_y),
    _range_z(range_z)
{}

bool Plane::is_in_range(Point3 p) {
    if (p.x < std::get<0>(this->_range_x) || p.x > std::get<1>(this->_range_x)) {
        return false;
    }
    if (p.y < std::get<0>(this->_range_y) || p.y > std::get<1>(this->_range_y)) {
        return false;
    }
    if (p.z < std::get<0>(this->_range_z) || p.z > std::get<1>(this->_range_z)) {
        return false;
    }

    return true;
}

bool Plane::hit(const Ray &ray, float t_min, float t_max, Hit_point &hit_pts) {
    auto dot_nb = dot_product(ray.get_direction(), this->_normal);

    if (dot_nb == 0) {
        return false;
    }

    auto diff = this->_p0 - ray.get_origin();
    float t = dot_product(diff, this->_normal) / dot_nb; // intersection point

    if (t < t_min || t > t_max) {
        return false;
    }

    // get the point using t
    t -= 1e-4;
    Point3 intersect_pts = ray.ray_at(t);

    // Check if the point is in the range
    if (!this->is_in_range(intersect_pts)) {
        return false;
    }

    //std::cout << intersect_pts << "\n\n";

    // set proper values in hit_pts
    hit_pts.normal = this->_normal;
    hit_pts.t = t;
    hit_pts.p = intersect_pts;
    hit_pts.material = this->_material;

    return true;
}
