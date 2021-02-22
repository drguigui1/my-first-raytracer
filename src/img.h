#pragma once

#include <vector>
#include <iostream>
#include <fstream>
#include <cstdio>

#include "vector3.h"

class Image {
    public:
        Image(int n_rows, int n_cols);

        // Save into ppm format
        void SavePPM(std::string path);

        int get_n_rows() { return this->n_rows; }
        int get_n_cols() { return this->n_cols; }

        void set_pixel(int i, int j, Color color) {
            this->pixels.at(i * this->n_cols + j) = color;
        }
        Color get_pixel(int i, int j) {
            return this->pixels.at(i * this->n_cols + j);
        }

    private:
        int n_rows;
        int n_cols;

        // vector of size n_rows * n_cols
        std::vector<Color> pixels;
};

std::ostream& operator<<(std::ostream& os, Image img);