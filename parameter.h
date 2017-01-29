#ifndef PARAMETER_H
#define PARAMETER_H

#define LSIZE 20.0 // changeable to resize

#include "def.h"
#include "object.h"

constexpr float lsize = LSIZE;
constexpr float rsize = lsize*2;

constexpr float lspace = lsize/2;
constexpr float rspace = rsize/3;

constexpr float arena_height = 6*lsize + 5*lspace;
constexpr float arena_width = 5*rsize + 4*rspace;

constexpr float margin0 = lsize*5.0/10;
constexpr float margin1 = lsize*27.0/10;
constexpr float margin2 = lsize*9.0/10;

constexpr float frame_size = margin0 + margin1 + margin2*2
                        + arena_height*2 + arena_width;

constexpr unsigned int corner = 22; // corner size for draw rounded rectangle

constexpr unsigned int whole_rank_size = 25;
constexpr rank_type whole_rank_set[] = {10, 100, 100, 100, 0, 0,
                                        30, 30, 30, 40, 39, 38, 38,
                                        37, 37, 36, 36, 35, 35,
                                        34, 34, 34, 33, 33, 33};


// define structure of coordinates
typedef struct // coordinates
{
    float x;
    float y;
} structxy;

structxy operator + (structxy, float);
structxy operator * (structxy, float);
structxy operator + (structxy, structxy);
structxy operator - (structxy, structxy);


// functions to determine coordinates
structxy coordinatexy(country_type country,
                      row_type row, col_type col,
                      float offset_x, float offset_y);
structxy coordinatexy(position p, float offset_x, float offset_y);
structxy get_top_left_corner(position p);
structxy get_size_xy(country_type country);



#endif // PARAMETER_H
