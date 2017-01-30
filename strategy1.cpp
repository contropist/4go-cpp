#ifndef STRATEGY1_CPP
#define STRATEGY1_CPP

//
#include "def.h"
#include "strategy1.h"
#include "route.h"
//

const float ratio = 0.35;

//
int score(rank_type rank)
{
    switch(rank)
    {
        case 10: return 500;
        case 40: return 40;
        case 39: return 30;
        case 38: return 20;
        case 37: return 10;
        case 36: return 4;
        case 35: return 3;
        case 0: return 23;
        case 30: return 7;
        case 100: return 3;
        default: return 2;
    }
}

//
int position_score(rank_type rank)
{
    switch(rank)
    {
        case 40: return 30;
        case 39: return 25;
        case 38: return 20;
        case 37: return 15;
        case 36: return 10;
        case 35: return 8;
        case 0: return 22;
        default: return 5;
    }
}

//
int under_attack(board & b, chess_type chess)
{
    int result = 0;

    position p(chess.code);

    if ((chess.state != empty) && !p.is_camp())
    {
        pos_list enemy_chesses = b.find_allies(right_country(chess.belong_to));

        for_int(i, enemy_chesses.size())
        {
            int_type e_code = enemy_chesses[i];
            position e_pos(e_code);
            chess_type e_chess = b.find_chess(e_code);

            if (e_chess.movable())
            {
                int beat = beat_it(e_chess.rank, chess.rank);

                if (beat == 1)
                {
                    pos_list move_list = route_list(b, e_chess, chess.code);
                    bool accessible = (move_list.size() > 1);

                    if (accessible)
                    {
                        return -score(chess.rank);
                    }
                }

                if (beat == 0)
                {
                    pos_list move_list = route_list(b, e_chess, chess.code);
                    bool accessible = (move_list.size() > 1);

                    if (accessible)
                    {
                        result = score(e_chess.rank) - score(chess.rank);
                        if (result > 0) result = 0;
                        return result;
                    }

                 }
               }
            }

        }

        return result;

}

//
int position_value(position pos, col_type flag_col)
{
    if (pos.country == middle) return 1;

    row_type row = pos.row;
    col_type col = pos.col;

    if (flag_col == 3)

        return position_value(position(pos.country, row, 4 - col), 1);

    else // flag_col == 1

        if (row == 5)
            switch (col)
            {
                case 0: return 5;
                case 1: return 0;
                case 2: return 5;
                case 3: return 0;
                default: return 1;
            }
        else if (row == 4)
            switch (col)
            {
                case 0: return 5;
                case 1: return 6;
                case 2: return 5;
                case 3: return 2;
                default: return 1;
            }
        else if (row == 3)
            switch (col)
            {
                case 1: return 5;
                case 2: return 2;
                case 3: return 2;
                default: return 1;
            }
        else if (row == 2)
            switch (col)
            {
                case 2: return 4;
                default: return 1;
            }
        else
            return 1;

}




//
float calculate_board(board & b, country_type now_turn)
{
    float sum = 1000.0, coefficient = 1.0, pos_coefficient = 0.0;
    col_type flag_col = 0;

    loop(i)
    {
        position pos(i);

        chess_type chess = b.find_chess(pos);
        if (chess.state == empty) continue;

        if (is_enemy(chess.belong_to, now_turn))
        {
            coefficient = -1.0;
        }
        else if (chess.belong_to == now_turn)
        {
            coefficient = 1.0;
        }
        else
        {
            coefficient = 1.0;
        }

        if (is_enemy(chess.belong_to, pos.country))
            coefficient *= 1.5;

        if (pos.country != middle)
        {

            if (b.find_chess(position(pos.country, 5, 1)).is_flag())
                flag_col = 1;
            else if (b.find_chess(position(pos.country, 5, 3)).is_flag())
                flag_col = 3;
            else
                flag_col = 0;

            if (flag_col != 0)
                pos_coefficient = 1/10 * position_score(chess.rank) * position_value(pos, flag_col);
            else
                pos_coefficient = 0.0;
        }

        sum += (score(chess.rank) + ratio * under_attack(b, chess))
                * coefficient
                + pos_coefficient; // * pos_coefficient;
    }

    return sum;
}

//
//
move_type run_strategy1(board & b, country_type belong_to)
{
    pos_list whole_list = b.find_belong_to(belong_to);
    move_type one_move;
    float value, max_value = -10000;

    for_int(i, whole_list.size())
    {
        int_type s_code = whole_list[i];
        position s_pos(s_code);
        chess_type s_chess = b.find_chess(s_code);

        if (s_chess.movable() && !s_pos.is_base())

            loop(d_code)
            {
                position d_pos(d_code);
                chess_type d_chess = b.find_chess(d_pos);

                bool eat_shit = d_pos.is_base() && (!d_chess.is_flag());

                pos_list move_list = route_list(b, s_chess, d_code);
                bool accessible = (move_list.size() > 1);

                if (accessible)
                {
                    if (b.go_able(s_chess, d_pos) && (!eat_shit))
                    {
                        board b2 = b;

                        b2.go_to(s_chess, d_chess);

                        value = calculate_board(b2, belong_to);

                        value += qrand() % 5;

                        if (value >= max_value)
                        {
                           max_value = value;

                           one_move.from = s_code;
                           one_move.to = d_code;
                        }
                    }
                  }
                }

    }

    return one_move;

}

#endif // STRATEGY1_CPP
