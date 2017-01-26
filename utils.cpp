#ifndef UTILS2_CPP
#define UTILS2_CPP

#include "utils.h"
#include "parameter.h"

bool within(int mouse_x, int mouse_y, structxy xy, structxy ab)
{
    float ratio_x = (mouse_x - xy.x)/ab.x;
    float ratio_y = (mouse_y - xy.y)/ab.y;

    return ( (ratio_x >= 0) && (ratio_x <= 1) &&
             (ratio_y >= 0) && (ratio_y <= 1) );
}

int search_xy(int mouse_x, int mouse_y)
{
    loop(i)
    {
        position p(i);
        structxy xy = get_top_left_corner(p);
        structxy ab = get_size_xy(p.country);

        if (within(mouse_x, mouse_y, xy, ab))
            return i;
    }

    return NOPOSITION;
}

#endif // UTILS2_CPP
