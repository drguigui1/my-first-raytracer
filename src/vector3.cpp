#include "vector3.h"

std::ostream& operator<<(std::ostream& os, Vector3 vector3) {
    os << "Vector3: \n";
    os << "x: " << vector3.x << "\ny: " << vector3.y << "\nz: " << vector3.z << '\n' ;
    return os;
}