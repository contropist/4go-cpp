#ifndef ROUTE_CPP
#define ROUTE_CPP

#include "def.h"
#include "object.h"

//
// move from one position to another position, according to current states of the board
// if somewhere is blocked, the move is not allowed, returns original position of length 1

// if the move is successful, returns the list of route, and prepare to move to or "fight with" the chess
// in destination.
pos_list route_list(chess_type from_chess, position to)
{
    pos_list route;
    int_type to_code = to.encode();

    position from(from_chess.code);

    route.push_back(from_chess.code);

    if ((from.country == to.country) &&
        ((abs(to.row - from.row) + abs(to.col - from.col) == 1) ||
         ((from.is_camp() || to.is_camp()) && (abs(to.row - from.row) == 1) && (abs(to.col - from.col) == 1))
       )) // one step cases

        route.push_back(to_code);


    return route;
}


#endif // OBJECT_CPP
