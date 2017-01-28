#ifndef LABOR_CPP
#define LABOR_CPP

//
#include "labor.h"
//


// function for labor_fly
void add_it(pos_list & route, country_type country, row_type row, col_type col) // add only if it is on rail and valid
{
    if (valid_position(country, row, col))
    {
        position pos(country, row, col);
        if (pos.on_rail())
            route.push_back(pos.encode());
    }
}

// function for labor_fly
pos_list neighbours_on_rail(position p)
{
    pos_list result;

    if (!p.on_rail()) return result;

    add_it(result, p.country, p.row + 1, p.col);
    add_it(result, p.country, p.row - 1, p.col);
    add_it(result, p.country, p.row, p.col + 1);
    add_it(result, p.country, p.row, p.col - 1);

    if ((p.country != middle) && (p.row == 0) && (p.col == 0))
        add_it(result, left_country(p.country), 0, 4);

    if ((p.country != middle) && (p.row == 0) && (p.col == 4))
        add_it(result, right_country(p.country), 0, 0);

    if ((p.country != middle) && (p.row == 0) && (p.col % 2 == 0))
    {
        int_type nearest = nearest_middle(p);
        add_it(result, middle, position(nearest).row, position(nearest).col);
    }

    if (p.country == middle)
        switch(p.row * 3 + p.col)
        {
            case 0:
                add_it(result, up, 0, 4);
                add_it(result, left, 0, 0);
            break;
            case 1:
                add_it(result, up, 0, 2);
            break;
            case 2:
                add_it(result, up, 0, 0);
                add_it(result, right, 0, 4);
            break;
            case 3:
                add_it(result, left, 0, 2);
            break;
            case 4:
            break;
            case 5:
                add_it(result, right, 0, 2);
            break;
            case 6:
                add_it(result, left, 0, 4);
                add_it(result, down, 0, 0);
            break;
            case 7:
                add_it(result, down, 0, 2);
            break;
            case 8:
                add_it(result, down, 0, 4);
                add_it(result, right, 0, 0);
            break;
            default:
                throw("Wrong input in neighbours_on_rail()");
        }

    return result;
}

//
bool member(int_type element, pos_list lst)
{
    size_t len = lst.size();

    for(size_t i = 0; i < len; i ++)
    {
        if (element == lst[i]) return true;
    }

    return false;
}

//
pos_list merge_all(branches & list_of_list) // with duplicates removed
{
    pos_list res_list, list_i;
    int_type item;

    size_t len = list_of_list.size();
    size_t len2, i, j;
    bool duplicate;

    for(i = 0; i < len; i ++)
    {
        list_i = list_of_list[i];
        len2 = list_i.size();
        for(j = 0; j < len2; j ++)
        {
            item = list_i[j];

            duplicate = member(item, res_list);

            if (!duplicate) res_list.push_back(item);
        }
    }

    return res_list;
}


// main function of labor_fly
// if the chess is a "labor", on the rail assumed
// a very hard to code module, requires lots of endeavor
//
pos_list search_next_step(board & b, branches fly_route_list, int_type from_code, int_type to_code)
{
    pos_list route, neighbours, new_route, empty_route;

    branches new_list;
    int_type final_pos, next_pos;

    pos_list passed_positions = merge_all(fly_route_list);

    size_t len = fly_route_list.size();
    for(size_t i = 0; i < len; i ++)
    {
        route = fly_route_list[i];

        final_pos = route[route.size() - 1];

        if (final_pos == to_code)
        {
            return route;
        }
        else
        {
            neighbours = neighbours_on_rail(final_pos);
            size_t len2 = neighbours.size();

            for(size_t j = 0; j < len2; j ++)
            {
                next_pos = neighbours[j];

                if ( ((!b.is_occupied(next_pos)) || (next_pos == to_code)) &&
                     (!member(next_pos, passed_positions)) )
                {
                    new_route = route;
                    new_route.push_back(next_pos);

                    new_list.push_back(new_route);
                }
            }
        }
    }

    if (new_list.size() == 0)
        return empty_route;
    else
        return search_next_step(b, new_list, from_code, to_code);

}

//
pos_list labor_fly_on_rail(board & b, int_type from_code, int_type to_code)
{
    pos_list origin;
    branches to_search_list;

    origin.push_back(from_code);
    to_search_list.push_back(origin);

    return search_next_step(b, to_search_list, from_code, to_code);

}



#endif // LABOR_CPP
