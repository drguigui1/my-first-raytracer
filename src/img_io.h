#pragma once

#include <string>
#include <memory>
#include <fstream>
#include <iostream>
#include <cstring>
#include <cstddef>

class rgb24_image {
    public:
        rgb24_image(int w, int h, uint8_t* pixels);
        rgb24_image() {}
        ~rgb24_image() {}

        int get_width() const { return this->_width; }
        int get_height() const { return this->_height; }
        int get_length() const { return this->_length; }
        uint8_t* get_pixels() const { return this->_pixels; }

    private:
        int _width;
        int _height;
        int _length;

        uint8_t* _pixels;

};

rgb24_image load_image(const char* filename);