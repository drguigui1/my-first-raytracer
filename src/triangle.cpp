#include "triangle.h"

Triangle::Triangle(Point3 p0, Point3 p1, Point3 p2, Material material) {
    this->_p0 = p0;
    this->_p1 = p1;
    this->_p2 = p2;
    this->_material = material;

    // compute edges
    this->_edge0 = p1 - p0;
    this->_edge1 = p2 - p1;
    this->_edge2 = p0 - p2;

    // compute normal
    this->_normal = unit_vector(cross_product(this->_edge0, p2 - p0));
}

bool Triangle::hit(const Ray &ray, float t_min, float t_max, Hit_point &hit_pts,
                   int i, int j) {
    // check if ray is parallele
    float dot_dir_n = dot_product(ray.get_direction(), this->_normal);

    if (std::abs(dot_dir_n) < 1e-5) {
        return false;
    }

    // t intersection value
    float t = (dot_product(this->_p0, this->_normal) - dot_product(ray.get_origin(), this->_normal)) / dot_dir_n;

    if (t < 0) {
        return false;
    }

    if (t < t_min || t > t_max) {
        return false;
    }

    // check if this point is in the triangle
    Point3 p = ray.ray_at(t);

    // case edge 0
    Vector3 vp0 = p - this->_p0;
    Vector3 c0 = cross_product(this->_edge0, vp0);

    if (dot_product(c0, this->_normal) < 0) {
        return false;
    }

    // case edge 1
    Vector3 vp1 = p - this->_p1;
    Vector3 c1 = cross_product(this->_edge1, vp1);

    if (dot_product(c1, this->_normal) < 0) {
        return false;
    }

    // case edge 2
    Vector3 vp2 = p - this->_p2;
    Vector3 c2 = cross_product(this->_edge2, vp2);

    if (dot_product(c2, this->_normal) < 0) {
        return false;
    }

    // set values
    t -= 1e-3;
    p = ray.ray_at(t);

    hit_pts.normal = (dot_dir_n > 0) ? this->_normal * -1.0 : this->_normal;
    hit_pts.p = p;
    hit_pts.t = t;
    hit_pts.material = this->_material;

    return true;
}
