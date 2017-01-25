#ifndef ROUTE_CPP
#define ROUTE_CPP

#include "def.h"
#include "object.h"

#include <vector>

// #include <algorithm>
//

typedef std::vector <pos_list> branches;

pos_list search_next_step(branches fly_route_list, int_type from_code, int_type to_code)
{
    pos_list chosen;
    branches new_list;
    int_type final_pos;


    chosen.push_back(from_code);

}


pos_list labor_fly(int_type from_code, int_type to_code)
// if the chess is a "labor", on the rail assumed
// a very hard to code module, requires lots of endeavor

{
    pos_list result;

    return result;

}


// route-list modules
/*
pos_list direct_row(country_type country, row_type row, row_type row2, col_type col)
{
    pos_list line;

    if (row == row2)
        line.push_back(position(country, row, col).encode());
    elseif (row2 > row)
    {
        line = direct_row(country, row + 1, row2, col);
        line.push_back(position(country, row, col).encode());
    }
    else
    {
        reverse(line.begin(), line.end());
    }

    return line;

}
*/





//
// move from one position to another position, according to current states of the board
// if somewhere is blocked, the move is not allowed, returns original position of length 1

// if the move is successful, returns the list of route, and prepare to move to or "fight with" the chess
// in destination.
pos_list board::route_list(chess_type from_chess, int_type to_code)
{
    pos_list route;
    int_type from_code = from_chess.code;
    position from(from_code), to(to_code);

    route.push_back(from_code);

    if ((from.country == to.country) &&
        ((abs(to.row - from.row) + abs(to.col - from.col) == 1) ||
         ((from.is_camp() || to.is_camp()) && (abs(to.row - from.row) == 1) && (abs(to.col - from.col) == 1))
       )) // one step cases

        route.push_back(to_code);

    if (from.on_rail() && to.on_rail())
    {
        if (from_chess.is_labor())
            route = labor_fly(from_code, to_code);
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
