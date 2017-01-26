#ifndef ROUTE_CPP
#define ROUTE_CPP

#include "def.h"
#include "object.h"
#include "route.h"

#include <vector>
#include <algorithm>
//

typedef std::vector <pos_list> branches;

//
// to test if an element exists in list
template <typename T> bool member(T element, std::vector <T> list)
{
    typename std::vector <T>::iterator ret;
    ret = std::find(list.begin(), list.end(), element);

    return (ret != list.end());

}

// add a position to a route if it is not occupied
void add(pos_list & route, int_type position_code, board & b)
{
    if (!b.is_occupied(position_code))
        route.push_back(position_code);
}

// closest neighbours on the rail
pos_list neighbours_on_rail(position p)
{
    pos_list neighbours;

    if (!p.on_rail()) throw("not on the rail when calling neighbours_on_rail");

    return neighbours;
}

//
// move from one position to another position, according to current states of the board
// if somewhere is blocked, the move is not allowed, returns original position of length 1

// if the move is successful, returns the list of route, and prepare to move to or "fight with" the chess
// in destination.
pos_list route_list(board & b, chess_type from_chess, int_type to_code)
{
    int_type from_code = from_chess.code;
    position from(from_code);
    position to(to_code);

    pos_list route;
    route.push_back(from_code); // starting point

    //

    // no moving
    if (from_code == to_code) return route;

    // one-step moving
    if ((from.country == to.country) &&
            ((abs(from.row - to.row) + abs(from.col - to.col) == 1) ||
             ((from.is_camp() || to.is_camp()) && (abs(from.row - to.row) == 1) && (abs(from.col - to.col) == 1))))
    {
        route.push_back(to_code);
        return route;
    }

    // moving on rail
    if (from.on_rail() && to.on_rail())
    {
        ;
    }

    return route;
}


#endif // ROUTE_CPP
