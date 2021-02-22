#pragma once

#include <iostream>

struct Color {
    Color(float r, float g, float b) : red(r), green(g), blue(b) {}
    Color() : red(0), green(0), blue(0) {}
    float red;
    float green;
    float blue;

    Color operator+(const float &l) const {
        auto new_r = this->red + l;
        auto new_g = this->green + l;
        auto new_b = this->blue + l;
        return Color(new_r, new_g, new_b);
    }

    Color operator-(const float &l) const {
        auto new_r = this->red - l;
        auto new_g = this->green - l;
        auto new_b = this->blue - l;
        return Color(new_r, new_g, new_b);
    }

    Color operator*(const float &l) const {
        auto new_r = this->red * l;
        auto new_g = this->green * l;
        auto new_b = this->blue * l;
        return Color(new_r, new_g, new_b);
    }
};

std::ostream& operator<<(std::ostream& os, Color color);