#ifndef PARAMETER_CPP
#define PARAMETER_CPP

//
#include "parameter.h"
#include "def.h"
#include "object.h"
//

//
structxy operator + (structxy xy, float r)
{
    return {xy.x + r, xy.y + r};
}

//
structxy operator * (structxy xy, float r)
{
    return {xy.x * r, xy.y * r};
}

//
structxy operator + (structxy xy, structxy xy2)
{
    return {xy.x + xy2.x, xy.y + xy2.y};
}

//
structxy operator - (structxy xy, structxy xy2)
{
    return {xy.x - xy2.x, xy.y - xy2.y};
}

//
//
structxy country_orientation(country_type country)
{
    switch (country)
    {
       case down:   return {0.0, 1.0};   break;
       case right:  return {1.0, 0.0};   break;
       case up:     return {0.0, -1.0};  break;
       case left:   return {-1.0, 0.0};  break;
       case middle: return {0.0, 0.0};   break;
       default: // error
          throw("Wrong country in calling right_country");

    }
}

// to locate the middle point of every country
structxy middle_point(country_type country)
{
    return country_orientation(country) * (arena_height/2 + arena_width/2 + margin2)
         + arena_height + arena_width/2
         + margin0 + margin2;
}

// vector x
structxy new_x(country_type country)
{
    structxy xy = country_orientation(country);

    return {xy.y, -xy.x};
}

// vector y
structxy new_y(country_type country)
{
    return country_orientation(country);
}

//
structxy starting_point(country_type country)
{
    structxy arena = {arena_width, arena_height};
    structxy half_arena = arena * 0.5;

    return middle_point(country)
         - new_x(country) * half_arena.x
         - new_y(country) * half_arena.y;
}

//
structxy coordinatexy(country_type country,
                      row_type row, col_type col,
                      float offset_x, float offset_y)
{
    if ((country == middle) && (row < row_num(country))
                            && (col < col_num(country)))

        return {coordinatexy(down, 0, col*2, offset_x, 0).x,
                coordinatexy(left, 0, row*2, offset_y, 0).y + rsize/4};

    else
        return starting_point(country)
             + new_x(country) * (col * (rsize + rspace) + offset_x * rsize)
             + new_y(country) * (row * (lsize + lspace) + offset_y * lsize);

}

//
structxy coordinatexy(position p, float offset_x, float offset_y)
{
    return coordinatexy(p.country, p.row, p.col, offset_x, offset_y);
}

//
structxy get_top_left_corner(position p)
{
    switch (p.country)
    {
       case middle:
       case down:  return coordinatexy(p, 0.0, 0.0); break;
       case right: return coordinatexy(p, 1.0, 0.0); break;
       case up:    return coordinatexy(p, 1.0, 1.0); break;
       case left:  return coordinatexy(p, 0.0, 1.0); break;
       default: // error
          throw("Wrong country in calling right_country");
    }

}

structxy get_size_xy(country_type country)
{
    switch (country)
    {
       case down:
       case up:
       case middle: return {rsize, lsize}; break;

       case right:
       case left:   return {lsize, rsize}; break;

       default: // error
          throw("Wrong country in calling right_country");
   }
}

#endif // PARAMETER_CPP
