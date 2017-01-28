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

//
bool test_occupied(board & b, pos_list & route) // test if occupied
{
    // do not test first and last element because they are from and to
    size_t len = route.size();

    if (len > 2)
        for(size_t i = 1; i < len - 1; i ++)
            if (b.is_occupied(route[i])) return true;

    return false;

}

//
void append(pos_list & route0, pos_list new_route)
{

    size_t len = new_route.size();

    for(size_t i = 0; i < len; i ++)
    {
        route0.push_back(new_route[i]);
    }
}

//
pos_list reverse_it(pos_list route)
{
    size_t len = route.size();
    pos_list reverse_route;

    for(size_t i = 0; i < len; i ++)
    {
        reverse_route.push_back(route[len - i - 1]);
    }

    return reverse_route;
}

//
bool can_go_out(position p)
{
    if (p.country == middle)
        throw("problem encountered in can_go_out()");

    return ((p.col == 0) && (p.row <= 4)) ||
           ((p.col == 2) && (p.row == 0)) ||
           ((p.col == 4) && (p.row <= 4));
}

//
int x_axis(country_type country)
{
    return (country == left)?1:((country == right)?-1:0);
}

int y_axis(country_type country)
{
    return (country == down)?1:((country == up)?-1:0);
}

//
int_type nearest_middle(position p)
{
    position p_nearest(middle, (p.col/2 - 1) * x_axis(p.country) + y_axis(p.country) + 1,
                               (p.col/2 - 1) * y_axis(p.country) - x_axis(p.country) + 1);
    return p_nearest.encode();
}

//
int_type front_line(position p)
{
    position p_front(p.country, 0, p.col);

    return p_front.encode();
}


//
pos_list route_rail(board & b, int_type from_code, int_type to_code) // without checking occupation
{
    pos_list route;
    position from(from_code);
    position to(to_code);
    row_type row;
    col_type col;

    if (from.country == to.country)
    {
        if ((from.row == to.row) && ((from.country == middle) || (from.row == 0) || (from.row == 4)))
        {
            if (from.col <= to.col)
                for(col = from.col; col <= to.col; col ++)
                    route.push_back(position(from.country, from.row, col).encode());
            else
                for(col = from.col; col >= to.col; col --)
                    route.push_back(position(from.country, from.row, col).encode());

        }

        else if ((from.col == to.col) && ((from.country == middle) ||
                                          ((from.row <= 4) && ((from.col == 0) || (from.col == 4)))))
        {
            if (from.row <= to.row)
                for(row = from.row; row <= to.row; row ++)
                    route.push_back(position(from.country, row, from.col).encode());
            else
                for(row = from.row; row >= to.row; row --)
                    route.push_back(position(from.country, row, from.col).encode());

        }
    }
    else if (to.country == middle)
    {
        if (can_go_out(from) && ((to.row - 1) * x_axis(from.country) +
                                 (to.col - 1) * y_axis(from.country) == from.col/2 - 1))
        {
            route = route_rail(b, from_code, front_line(from));
            append(route, route_rail(b, nearest_middle(from), to_code));

        }
    }
    else if (from.country == middle)
        route = reverse_it(route_rail(b, to_code, from_code));

    else if (to.country == ally_country(from.country))
    {
        if (can_go_out(from) && can_go_out(to) && (from.col + to.col == 4))
        {
            route = route_rail(b, from_code, front_line(from));
            append(route, route_rail(b, nearest_middle(from), nearest_middle(to)));
            append(route, route_rail(b, front_line(to), to_code));
        }
    }
    else if (to.country == right_country(from.country))
    {
        if ((from.col == 4) && (from.row <= 4) && (to.col == 0) && (to.row <= 4))
        {
            route = route_rail(b, from_code, position(from.country, 0, from.col).encode());
            append(route, route_rail(b, position(to.country, 0, to.col).encode(), to_code));
        }
    }
    else if (to.country == left_country(from.country))
    {
        if ((from.col == 0) && (from.row <= 4) && (to.col == 4) && (to.row <= 4))
        {
            route = route_rail(b, from_code, position(from.country, 0, from.col).encode());
            append(route, route_rail(b, position(to.country, 0, to.col).encode(), to_code));
        }
    }
    else
        throw("problem encountered when calling route_rail()");

    return route;

}

pos_list route_on_rail(board & b, int_type from_code, int_type to_code) // check occupied or not
{
    pos_list empty_route,
             route = route_rail(b, from_code, to_code);

    if (!test_occupied(b, route))
        return route;
    else
        return empty_route;


}

//
// move from one position to another position, according to current states of the board
// if somewhere is blocked, the move is not allowed, returns an empty list
// if the starting point is same as destination, returns original position of length 1

// if the move is successful, returns the list of route, and prepare to move to or "fight with" the chess
// in destination.
pos_list route_list(board & b, chess_type from_chess, int_type to_code)
{
    int_type from_code = from_chess.code;
    position from(from_code);
    position to(to_code);
    pos_list route, one_element_route;

    //

    // no moving
    if (from_code == to_code)
    {
        one_element_route.push_back(from_code);
        return one_element_route;
    }

    // one-step moving
    if ((from.country == to.country) &&
            ((abs(from.row - to.row) + abs(from.col - to.col) == 1) ||
             ((from.is_camp() || to.is_camp()) && (abs(from.row - to.row) == 1) && (abs(from.col - to.col) == 1))))
    {
        route.push_back(from_code); // starting point
        route.push_back(to_code);
        return route;
    }

    // moving on rail
    if (from.on_rail() && to.on_rail())
    {
        if (from_chess.is_labor())
            return route_on_rail(b, from_code, to_code);
      //    return labor_fly_on_rail(b, from_code, to_code);
        else
            return route_on_rail(b, from_code, to_code);
    }

    return route;

}


#endif // ROUTE_CPP
