#ifndef COLOUR_H
#define COLOUR_H

#include "interval.h"
#include "vec3.h"

using colour = vec3;

inline double linear_to_gamma(double linear_component)
{
    if (linear_component > 0)
        return std::sqrt(linear_component);

    return 0;
}

void write_colour(unsigned char* image, int base_index, const colour& pixel_colour) {
    auto r = pixel_colour.x();
    auto g = pixel_colour.y();
    auto b = pixel_colour.z();

    // Apply a linear_to_gamma transform for gamma 2
    r = linear_to_gamma(r);
    g = linear_to_gamma(g);
    b = linear_to_gamma(b);

    image[base_index + 2] = static_cast<unsigned char>(255.999 * r);
    image[base_index + 1] = static_cast<unsigned char>(255.999 * g);
    image[base_index + 0] = static_cast<unsigned char>(255.999 * b);
}


#endif