#include "color.h"

std::ostream& operator<<(std::ostream& os, Color color) {
    os << "Color: \n";
    os << "Red: " << color.red << "\nGreen: " << color.green << "\nBlue: " << color.blue << '\n';
    return os;
}