#ifndef DRAW_BOARD_CPP
#define DRAW_BOARD_CPP

#include "main.h"
#include "utils.h"

void draw_empty_chess(country_type, int, int);
void draw_board();
void draw_middle();

//
void draw_board()
{
    for (country_type country = down; country < down; country ++)
        for (int row = 0; row < row_num(country); row ++)
             for (int col = 0; col < col_num(country); col ++)

                 draw_empty_chess(country, row, col);

}

void draw_empty_chess(country_type country, int row, int col)
{

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
