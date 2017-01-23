#ifndef UTILS_CPP
#define UTILS_CPP

#include "utils.h"
#include "parameter.h"

//
void draw_chess(QPainter * paint,
                chess_type c)
{
    position p(c.code);
    country_type country = p.country;

    structxy xy = get_top_left_corner(p);
    structxy ab = get_size_xy(country);
    float iota = 0.1; // small offset

    return;
}

#endif // UTILS_CPP
