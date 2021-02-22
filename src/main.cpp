#include "point.h"
#include "vector3.h"
#include "img.h"

int main() {
    Image img = Image(50, 50);
    auto c = Color(255, 255, 0);

    for (int i = 20; i < 40; i++) {
        for (int j = 20; j < 40; j++) {
            img.set_pixel(i, j, c);
        }
    }
    img.SavePPM("test.ppm");
}