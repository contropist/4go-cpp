#ifndef ROUTE_CPP
#define ROUTE_CPP

#include "def.h"
#include "object.h"

// route-list modules
// direct_row(country_type country, row_type row, row_type row2, col_type col)
//{


//
// move from one position to another position, according to current states of the board
// if somewhere is blocked, the move is not allowed, returns original position of length 1

// if the move is successful, returns the list of route, and prepare to move to or "fight with" the chess
// in destination.
pos_list board::route_list(chess_type from_chess, int_type to_code)
{
    pos_list route;
    position to(to_code);
    position from(from_chess.code);

    route.push_back(from_chess.code);

    if ((from.country == to.country) &&
        ((abs(to.row - from.row) + abs(to.col - from.col) == 1) ||
         ((from.is_camp() || to.is_camp()) && (abs(to.row - from.row) == 1) && (abs(to.col - from.col) == 1))
       )) // one step cases

        route.push_back(to_code);

    if (from.on_rail() && to.on_rail())
    {
        if (from_chess.is_labor())
            ; //route = labor_fly(from, to);
        else
        {
            if ((from.country == to.country) &&
                ((from.row == 0) ||
                 (from.row == 4) ||
                 (from.row == to.row)))
                ;
        };

    }

    return route;
}


#endif // OBJECT_CPP
