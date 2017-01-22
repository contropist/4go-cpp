#ifndef DRAW_BOARD_CPP
#define DRAW_BOARD_CPP

#include "parameter.h"
#include "utils.h"

void draw_empty_chess(country_type, int, int);
void draw_board();
void draw_middle();

//
void draw_board()
{
    for (country_type country = down; country != down; ++ country)
        for (int row = 0; row < row_num(country); row ++)
             for (int col = 0; col < col_num(country); col ++)

                 draw_empty_chess(country, row, col);

}

void draw_empty_chess(country_type country, int row, int col)
{

    structxy xy = get_top_left_corner(country, row, col);
    structxy ab = get_size_xy(country);
    structxy xy2 = coordinatexy(country, row, col, 1.0, 1.0/2);
    structxy xyn = coordinatexy(country, row, col+1, 0.0, 1.0/2);
    structxy xy3 = coordinatexy(country, row, col, 1.0/2, 1.0);
    structxy xyd = coordinatexy(country, row+1, col, 1.0/2, 0.0);
    structxy xy0 = coordinatexy(country, row, col, 1.0/2, 1.0/2);
    float radius1 = ab.x/2;
    float radius2 = ab.y/2;

    return;

}


void draw_middle()
{

    return;

}

//
void draw_chess_board()
{
    draw_board();
    draw_middle();

}

#endif // DRAW_BOARD_CPP
