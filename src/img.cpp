#include "img.h"

Image::Image(int n_rows, int n_cols) {
    this->n_rows = n_rows;
    this->n_cols = n_cols;

    std::vector<Color> vec;
    vec.reserve(n_rows * n_cols);

    for (int i = 0; i < this->n_rows; i++) {
        for (int j = 0; j < this->n_cols; j++) {
            Color c = Color();
            vec.push_back(c);
        }
    }
    this->pixels = vec; 
}

void Image::SavePPM(std::string path) {
    std::ofstream ofs(path, std::ios_base::out | std::ios_base::binary);
    ofs << "P6" << ' ' << this->n_cols << ' ' << this->n_rows << ' ' << "255" << '\n';

    for (int i = 0; i < this->n_rows; i++) {
        for (int j = 0; j < this->n_cols; j++) {
            auto c = this->get_pixel(i, j);
            ofs << (char) c.x << (char) c.y << (char) c.z;
        }
    }

    ofs.close();
}

std::ostream& operator<<(std::ostream& os, Image img) {
    for (int i = 0; i < img.get_n_rows(); i++) {
        for (int j = 0; j < img.get_n_cols(); j++) {
            os << img.get_pixel(i, j) << '\n';
        }
        os << "----\n";
    }

    return os;
}