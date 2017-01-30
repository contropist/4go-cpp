#ifndef OBJECT_CPP
#define OBJECT_CPP

#include "object.h"
#include "def.h"
#include "drawchess.h"
#include "route.h"

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

position::position(country_type c, row_type r, col_type cl)
{
    if (!valid_position(c, r, cl) &&
            !((r == 5) && (cl == 5)) ) // to allow extra flag out of boundary

        throw("Invalid arguments for position::position()"); // error
    else
    {
       country = c;
       row = r;
       col = cl;
    }
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

//
// chess
//

chess_type::chess_type()
{
    set_empty(0);
}

chess_type::chess_type(rank_type r, country_type b, state_type s, int_type c)
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

bool chess_type::is_empty()
{
    return (state == empty);
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
    return !chesses[position_code].is_empty();
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

pos_list board::find_state(state_type st)
{
    pos_list l;

    loop(i)
    {
        if (chesses[i].state == st)
            l.push_back(i);
    }

    return l;
}

pos_list board::find_rank(rank_type r)
{
    pos_list l;

    loop(i)
    {
        if (chesses[i].rank == r)
            l.push_back(i);
    }

    return l;
}

pos_list board::find_rank(rank_type r, pos_list search_scope)
{
    pos_list l;

    for_int(k, search_scope.size())
    {
        int_type i = search_scope[k];

        if (chesses[i].rank == r)
            l.push_back(i);
    }

    return l;
}


pos_list board::find_belong_to(country_type belong_to)
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
             (chesses[i].belong_to == right_country(belong_to, 2)) )
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

bool board::go_able(chess_type chess1, position pos2)
{
    if (!is_occupied(pos2)) return true;

    chess_type chess2 = find_chess(pos2);

    if (is_enemy(chess1.belong_to, chess2.belong_to) &&
        (!pos2.is_camp()))
        return true;

    return false;

}

bool board::cannot_move(country_type belong_to)
{

    pos_list all_chesses = find_belong_to(belong_to);

    size_t len = all_chesses.size();
    for(size_t i = 0; i < len; i ++)
    {
        int_type s_code = all_chesses[i];
        position s_pos(s_code);
        chess_type s_chess = find_chess(s_code);

        if (!s_chess.movable() || s_pos.is_base()) continue;

        loop(possible_position)
        {
            position p_pos(possible_position);

            if (!go_able(s_chess, p_pos)) continue;

            pos_list move_list = route_list(*this, s_chess, possible_position);
            if (move_list.size() > 1) return false;
        }
    }

    return true;
}

void board::go_to(chess_type chess1, chess_type chess2)
{
    int beat;

    if (chess2.is_empty()) // empty position
    {
         occupy(chess2.code, chess1.rank, chess1.belong_to, normal);
    }

    else
    {
        beat = beat_it(chess1.rank, chess2.rank);

        remove_position(chess2.code);

        if (beat == -1)
            occupy(chess2.code, chess2.rank, chess2.belong_to, normal);

        if (beat >= 0)
            if (chess2.is_flag())
                    delete_belong_to(chess2.belong_to);

        if (beat == 1)
            occupy(chess2.code, chess1.rank, chess1.belong_to, normal);
    }

    // erase the original position
    if (!chess1.is_empty())
    {
        remove_position(chess1.code);
    }

}


#endif // OBJECT_CPP
