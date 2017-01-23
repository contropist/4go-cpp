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

    QColor color;

    switch (c.belong_to)
    {
        case down: color = Qt::red; break;
        case right: color = Qt::yellow; break;
        case up: color = Qt::blue; break;
        case left: color = Qt::green; break;
        default: color = Qt::gray;
    }


}

#endif // UTILS_CPP
