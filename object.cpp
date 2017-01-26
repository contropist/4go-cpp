#ifndef OBJECT_CPP
#define OBJECT_CPP

#include "object.h"
#include "def.h"
#include "drawchess.h"

//
// position
//
int_type position::encode()
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
        return MAXPOS0 + row * 3 + col;

}

position::position(int_type code)
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


    if (r < row_num(co))
       row = r;
    else
       throw("Wrong row number"); // error


    if (cl < col_num(co))
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
    return (
             (row < (row_num(country))) &&
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

chess_type::chess_type(rank_type r, country_type b, state_type s, int c)
{
    rank = r;
    belong_to = b;
    state = s;
    code = c;
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
    loop(i)
    {
        chesses[i].set_empty(i);
    }

    which_turn = down;

}


void board::occupy(int_type position_code, rank_type rank, country_type belong_to, state_type state)
{

    chess_type chess(rank, belong_to, state, position_code);
    chesses[position_code] = chess;

}

void board::occupy(position p, rank_type rank, country_type belong_to, state_type state)
{

    occupy(p.encode(), rank, belong_to, state);

}

void board::remove_position(int_type position_code)
{
    chesses[position_code].set_empty(position_code);
}

void board::remove_position(position p)
{
    remove_position(p.encode());
}

void board::change_state(int_type position_code, state_type new_state)
{
    chesses[position_code].state = new_state;
}

void board::change_state(position p, state_type new_state)
{
    change_state(p.encode(), new_state);
}

bool board::is_occupied(int_type position_code)
{
    return (chesses[position_code].state != empty);
}

bool board::is_occupied(position p)
{
    return is_occupied(p.encode());
}

void board::delete_belong_to(country_type belong_to) // according to belong_to
{
    loop(i)
    {
        if (chesses[i].belong_to == belong_to)
            chesses[i].set_empty(i);
    }
}

bool board::is_empty(country_type belong_to) // according to belong_to
{
    loop(i)
    {
        if (chesses[i].belong_to == belong_to)
            return false;
    }

    return true;
}

pos_list board::find(state_type st)
{
    pos_list l;

    loop(i)
    {
        if (chesses[i].state == st)
            l.push_back(i);
    }

    return l;
}

pos_list board::find(rank_type r)
{
    pos_list l;

    loop(i)
    {
        if (chesses[i].rank == r)
            l.push_back(i);
    }

    return l;
}

pos_list board::find(country_type belong_to)
{
    pos_list l;

    loop(i)
    {
        if (chesses[i].belong_to == belong_to)
            l.push_back(i);
    }

    return l;
}

pos_list board::find_allies(country_type belong_to)
{
    pos_list l;

    loop(i)
    {
        if ( (chesses[i].belong_to == belong_to) ||
             (chesses[i].belong_to == ally(belong_to)) )
            l.push_back(i);
    }

    return l;
}


pos_list board::find_country(country_type country)
{
    pos_list l;

    loop(i)
    {
        position p(i);

        if (p.country == country)
            l.push_back(i);
    }

    return l;
}

chess_type board::find_chess(int_type position_code)
{
    return chesses[position_code];
}

chess_type board::find_chess(position p)
{
    return find_chess(p.encode());
}

void board::draw_all_chesses(QPainter * paint)
{
    loop(i)
    {
        if (chesses[i].state != empty)
            draw_chess(paint, chesses[i]);
    }

}


#endif // OBJECT_CPP
