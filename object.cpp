#ifndef OBJECT_CPP
#define OBJECT_CPP

#include "object.h"
#include "utils.h"

//
// position
//
position::position(country_type c, row_type r, col_type cl)
{
    country = c;
    row = r;
    col = cl;
}

bool position::is_camp()
{
    return ( (country != middle) &&
             (row >= 1) &&
             (row <= 3) &&
             ( (row == col) || (row + col == 4) )
           );
}

bool position::is_base()
{
    return ( (country != middle) &&
             (row == 5) &&
             ( (col == 1) || (col == 3) )
           );
}

bool position::on_rail()
{
    return ( (country == middle) ||
             (row == 0) ||
             (row == 4) ||
             ( (row < 5) && ( (col == 0) || (col == 4) ) )
           );
}

bool position::valid()
{
    return ( (row >= 0) &&
             (row < (row_num(country))) &&
             (col >= 0) &&
             (col < (col_num(country)))
           );
}

//
// chess
//
bool chess::is_labor()
{
    return (rank == 30);
}

bool chess::is_flag()
{
    return (rank == 10);
}

bool chess::movable()
{
    return (!
            ( (rank == 10) || (rank == 100) )
           );
}

//
// board
//
board::board()
{
    occupied_list = NULL;
}

void board::occupy(chess c)
{
    //
    return;
}

void board::delete_position(position p)
{
    //
    return;
}


#endif // OBJECT_CPP
