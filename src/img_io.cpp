#include "img_io.h"

rgb24_image::rgb24_image(int w, int h, uint8_t* pixels) {
    this->_width = w;
    this->_height = h;
    this->_pixels = pixels;
}

rgb24_image load_image(const char* filename) {
    std::ifstream infile(filename, std::ifstream::binary);
    if (!infile.is_open())
    {
        std::cout << "Failed to open " << filename << std::endl;
        return rgb24_image(0, 0, nullptr);
    }

    std::string mMagic;
    infile >> mMagic;
    infile.seekg(1, infile.cur);
    char c;
    infile.get(c);
    if (c == '#')
    {
        // We got comments in the PPM image and skip the comments
        while (c != '\n')
        {
            infile.get(c);
        }
    }
    else
    {
        infile.seekg(-1, infile.cur);
    }

    int mW, mH, mMax;

    infile >> mW >> mH >> mMax;
    if (mMax != 255)
    {
        std::cout << "Failed to read " << filename << std::endl;
        std::cout << "Got PPM maximum value: " << mMax << std::endl;
        std::cout << "Maximum pixel has to be 255" << std::endl;
        return rgb24_image(0, 0, nullptr);
    }

    auto mBuffer = new uint8_t[mW * mH * 3];

    // ASCII
    if (mMagic == "P3")
    {
        for (int i = 0; i < mW * mH * 3; i ++)
        {
            std::string pixel_str;
            infile >> pixel_str;
            mBuffer[i] = static_cast<uint8_t> (std::stoi(pixel_str));
        }
    }
    // Binary
    else if (mMagic == "P6")
    {
        // Move curser once to skip '\n'
        infile.seekg(1, infile.cur);
        infile.read(reinterpret_cast<char *>(mBuffer), mW * mH * 3);
    }
    else
    {
        std::cout << "Unrecognized PPM format" << std::endl;
        std::cout << "Got PPM magic number: " << mMagic << std::endl;
        std::cout << "PPM magic number should be either P3 or P6" << std::endl;
        return rgb24_image(0, 0, nullptr);
    }

    auto img = rgb24_image(mW, mH, mBuffer);

    return img;
}