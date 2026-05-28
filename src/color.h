#ifndef COLOR_H
#define COLOR_H

#include "vec3.h"
#include <iostream>

// Encapsulate the color writing logic
void write_color(std::ofstream &out, const color& pixel_color) {
    // Write the translated [0,255] value of each color component.
    
    int tempVarX = static_cast<int>(255.999 * pixel_color.x());
    int tempVarY = static_cast<int>(255.999 * pixel_color.y());
    int tempVarZ = static_cast<int>(255.999 * pixel_color.z());

    out << tempVarX << ' ' << tempVarY << ' ' << tempVarZ << '\n';
}

#endif