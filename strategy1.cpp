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
int position_value(row_type row, col_type col, col_type flag_col)
{
    if (flag_col == 3)

        return position_value(row, 4 - col, 1);

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



float calculate_value(board & b, country_type belong_to)
{
    pos_list all_chess = b.find(belong_to);
    float sum = 0, coefficient = 1.0, pos_coefficient = 1.0;
    col_type flag_col;

    if (b.is_empty(belong_to)) return 0;

    for_int(i, all_chess.size())
    {
        int_type pos_code = all_chess[i];
        position pos(pos_code);

        chess_type chess = b.find_chess(pos_code);

        if (pos.country == belong_to) // occupy self' position
            coefficient = 1.1;
        else if ((!b.is_empty(pos.country)) && is_enemy(pos.country, belong_to)) // occupied enemy's position
            coefficient = 1.4;
        else
            coefficient = 1.0;

        if ((!b.is_empty(pos.country)) && (pos.country != middle))
        {
            if (b.find_chess(position(pos.country, 5, 1)).is_flag())
                flag_col = 1;
            else
                flag_col = 3;

            pos_coefficient = 1.0 + (position_value(pos.row, pos.col, flag_col) - 1) * 0.1;
        }


        sum += score(chess.rank) * coefficient * pos_coefficient;

        sum += ratio * under_attack(b, chess) * coefficient * pos_coefficient;
    }

    return sum;
}



//
//
move_type run_strategy1(board &b, country_type belong_to)
{
    pos_list whole_list = b.find(belong_to);
    move_type one_move;
    float max_value = -10000;

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

                pos_list move_list = route_list(b, s_chess, d_code);
                bool accessible = (move_list.size() > 1);

                bool go_able = (!b.is_occupied(d_code)) ||
                        (b.is_occupied(d_code) && is_enemy(s_chess.belong_to, d_chess.belong_to) &&
                         (!d_pos.is_camp()) && (!(d_pos.is_base() && (d_chess.rank != 10))))
                        ;

                if (accessible && go_able)
                {
                    board b2 = b;

                    b2.remove_position(s_code);

                    if (!b2.is_occupied(d_code))

                        b2.occupy(d_pos, s_chess.rank, s_chess.belong_to, normal);

                    else
                    {
                        switch(beat_it(s_chess.rank, d_chess.rank))
                        {
                            case 1:
                                    b2.remove_position(d_code);
                                    if (d_chess.is_flag())
                                    {
                                        b2.delete_belong_to(d_chess.belong_to);
                                    }
                                    b2.occupy(d_pos, s_chess.rank, s_chess.belong_to, normal);
                                    break;
                            case 0:
                                    b2.remove_position(d_code);
                                    if (d_chess.is_flag())
                                    {
                                        b2.delete_belong_to(d_chess.belong_to);
                                    }
                                    break;
                                    break;
                            default: ;
                        }
                     }

                     float value = calculate_value(b2, belong_to)
                                 + calculate_value(b2, ally_country(belong_to))
                                 - calculate_value(b2, right_country(belong_to))
                                 - calculate_value(b2, left_country(belong_to))
                             ;

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

    return one_move;

}

#endif // STRATEGY1_CPP
