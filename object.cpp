#ifndef OBJECT_CPP
#define OBJECT_CPP

#include "object.h"
#include "def.h"

//
// position
//
int position::encode()
{
    int c_code;

    switch (country)
    {
        case down:  c_code = 0; break;
        case right: c_code = 1; break;
        case up:    c_code = 2; break;
        case left:  c_code = 3; break;
        case middle:c_code = 4; break;
        default: throw("error in calling encode()");
    }

    if (c_code <= 3)
        return c_code * 30 + row * 5 + col;
    else
        return c_code * 30 + row * 3 + col;

}

position::position(int code)
{
    int r = code % 30;
    int c = (code - r) / 30;

    switch (c)
    {
        case 0: country = down;  break;
        case 1: country = right; break;
        case 2: country = up;    break;
        case 3: country = left;  break;
        case 4: country = middle;break;
        default: throw("error in decoding position");
    }

    if (c <= 3)
    {
        col = r % 5;
        row = (r - col) / 5;
    }
    else
    {
        col = r % 3;
        row = (r - col) / 3;
    }
}

position::position(country_type co, row_type r, col_type cl)
{
    if (co != null)
        country = co;
    else
        throw("Wrong country name");


    if ( (r >= 0) && (r < row_num(co)) )
       row = r;
    else
       throw("Wrong row number"); // error


    if ( (cl >= 0) && (cl < col_num(co)) )
       col = cl;
    else
       throw("Wrong col number"); // error
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

chess_type::chess_type()
{
    set_empty(0);
}

void chess_type::set_empty(int c)
{
    rank = NORANK;
    belong_to = null;
    state = empty;
    code = c;
}

bool chess_type::is_labor()
{
    return (rank == 30);
}

bool chess_type::is_flag()
{
    return (rank == 10);
}

bool chess_type::movable()
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
    for (int i = 0; i < MAXPOS; i ++)
        chesses[i].set_empty(i);

}


void board::occupy(chess_type chess, position p)
{

    int code = p.encode();

    chesses[code] = chess;

}

void board::delete_position(position p)
{
    int code = p.encode();

    chesses[code].set_empty(code);
}

bool board::is_occupied(position p)
{
    int code = p.encode();

    return (chesses[code].state != empty);

}

void board::delete_belong_to(country_type belong_to) // according to belong_to
{
    for (int i = 0; i < MAXPOS; i ++)
        if (chesses[i].belong_to == belong_to)
            chesses[i].set_empty(i);
}

bool board::is_empty(country_type belong_to) // according to belong_to
{
    for (int i = 0; i < MAXPOS; i ++)
        if (chesses[i].belong_to == belong_to)
            return false;

    return true;
}

pos_list board::find(state_type st)
{
    pos_list l;

    for (int i = 0; i < MAXPOS; i ++)
        if (chesses[i].state == st)
            l.push_back(i);

    return l;
}

pos_list board::find(rank_type r)
{
    pos_list l;

    for (int i = 0; i < MAXPOS; i ++)
        if (chesses[i].rank == r)
            l.push_back(i);

    return l;
}

pos_list board::find(country_type belong_to)
{
    pos_list l;

    for (int i = 0; i < MAXPOS; i ++)
        if (chesses[i].belong_to == belong_to)
            l.push_back(i);

    return l;
}

pos_list board::find_allies(country_type belong_to)
{
    pos_list l;

    for (int i = 0; i < MAXPOS; i ++)
        if ( (chesses[i].belong_to == belong_to) ||
             (chesses[i].belong_to == ally(belong_to)) )
            l.push_back(i);

    return l;
}


pos_list board::find_country(country_type country)
{
    pos_list l;

    for (int i = 0; i < MAXPOS; i ++)
    {
        position p(i);

        if (p.country == country)
            l.push_back(i);
    }

    return l;
}


#endif // OBJECT_CPP
