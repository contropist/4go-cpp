#ifndef ROUTE_CPP
#define ROUTE_CPP

#include "def.h"
#include "object.h"

#include <vector>

#include <algorithm>
//

typedef std::vector <pos_list> branches;

//
template <typename T>
bool member(T element, std::vector <T> list)
{
    typename std::vector <T>::iterator ret;
    ret = std::find(list.begin(), list.end(), element);

    if (ret == list.end())
        return false;
    else
        return true;

}

//
pos_list neighbours_on_rail(int_type position_code)
{
    pos_list they, neighbours;
    position p(position_code);

    neighbours.push_back(position(p.country, p.row + 1, p.col).encode());
    neighbours.push_back(position(p.country, p.row - 1, p.col).encode());
    neighbours.push_back(position(p.country, p.row, p.col + 1).encode());
    neighbours.push_back(position(p.country, p.row, p.col - 1).encode());

    if ((p.country != middle) && (p.row == 0) && (p.col == 0))
        neighbours.insert(neighbours.begin(), position(left_country(p.country), 0, 4).encode());
    else if ((p.country != middle) && (p.row == 0) && (p.col == 4))
        neighbours.insert(neighbours.begin(), position(right_country(p.country), 0, 4).encode());
    else if ((p.country != middle) && (p.row == 0) && (p.col % 2 == 0))
        switch (p.country)
        {
            case down:
                neighbours.insert(neighbours.begin(), position(middle, 2, p.col/2).encode()); break;
            case up:
                neighbours.insert(neighbours.begin(), position(middle, 0, 2 - p.col/2).encode()); break;
            case left:
                neighbours.insert(neighbours.begin(), position(middle, p.col/2, 0).encode()); break;
            case right:
                neighbours.insert(neighbours.begin(), position(middle, 2 - p.col/2, 2).encode()); break;
            default: ;
        }
     else if (p.country == middle)
     {
         unsigned int counter = 0;
         country_type country2; col_type col2;
         for (country2 = down; counter < 4; country2 ++, counter ++)
             for (col2 = 0; col2 <= 4; col2 += 2)
                 if (member(position_code, neighbours_on_rail(position(country2, 0, col2).encode())))
                     neighbours.insert(neighbours.begin(), position(country2, 0, col2).encode());
    }
    else
        // error
        return they;
}

//
pos_list search_next_step(board & b, branches fly_route_list, int_type from_code, int_type to_code)
{
    branches new_list;
    int_type final_pos, next_pos;
    pos_list origin, chosen, passed_positions, route, new_route, neighbours;
    size_t i, j;

    origin.push_back(from_code);

    // merge fly_route_list and remove duplicates
    // to passed_positions
    // key factor to become faster
    pos_list fly_route;

    size_t len = fly_route_list.size();
    for(i = 0; i < len; i ++)
    {
        fly_route = fly_route_list[i];

        size_t len_fly_route = fly_route.size();
        for(j = 0; j < len_fly_route; j ++)
            // test if passed_positions already contains the element
            // if not, add it
            if (!member(fly_route[j], passed_positions))
                passed_positions.push_back(fly_route[j]); // merged
    }

    bool quit = false;
    chosen = origin;

    for(i = 0; i < len; i ++)
    {
        route = fly_route_list[i];

        final_pos = route.back();
        if (final_pos == to_code)
        {
            chosen = route;
            quit = true;
            break;
        }
        else
        {
            neighbours = neighbours_on_rail(final_pos);

            size_t len_neighbours = neighbours.size();
            for(j = 0; j < len_neighbours; j ++)
            {
                next_pos = neighbours[j];

                if (((!b.is_occupied(next_pos)) || (next_pos == to_code)) &&
                    (!member(next_pos, passed_positions)))
                    // have to ensure the route does not pass the same place twice
                {
                    new_route = route;
                    new_route.push_back(next_pos);

                    new_list.push_back(new_route);
                }
            }

        }

    }

    if (quit)

        return chosen;

    else if (new_list.empty())

        return origin;

    else

        return search_next_step(b, new_list, from_code, to_code);

}


pos_list labor_fly(int_type from_code, int_type to_code)
// if the chess is a "labor", on the rail assumed
// a very hard to code module, requires lots of endeavor

{
    pos_list result;

    return result;

}


// route-list modules





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
