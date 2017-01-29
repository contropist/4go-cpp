#ifndef STRATEGY0_CPP
#define STRATEGY0_CPP

//
#include "def.h"
#include "strategy0.h"
#include "route.h"
//

int score_0(rank_type rank)
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
        case 0: return 22;
        case 30: return 6;
        case 100: return 3;
        default: return 2;
    }
}

//
bool under_attack_0(board & b, chess_type chess)
{
    position pos(chess.code);

    if ((chess.state != empty) && !pos.is_camp())
    {
        pos_list enemy_chesses = b.find_allies(right_country(chess.belong_to));

        for_int(i, enemy_chesses.size())
        {
            int_type e_code = enemy_chesses[i];
            chess_type e_chess = b.find_chess(e_code);

            if (e_chess.movable() &&
                ((beat_it(e_chess.rank, chess.rank) == 1) || (e_chess.rank == 0)))
            {
                pos_list move_list = route_list(b, e_chess, chess.code);
                bool accessible = (move_list.size() > 1);

                if (accessible)
                    return true;
            }
        }
    }

    return false;
}

//
void extra_score(board & b, int & sum, country_type belong_to, row_type e_row, col_type e_col, int e_score)
{
    position p(belong_to, e_row, e_col);

    if (b.is_occupied(p))
    {
        country_type which_side = b.find_chess(p).belong_to;

        if (is_enemy(which_side, belong_to))
            sum -= e_score;
    }
}

//
int calculate_value_0(board & b, country_type belong_to)
{
    pos_list all_chess = b.find(belong_to);
    int sum = 0;

    if (b.is_empty(belong_to)) return 0;

    for_int(i, all_chess.size())
    {
        int_type pos = all_chess[i];
        chess_type chess = b.find_chess(pos);

        sum += score_0(chess.rank);

        if (position(pos).is_camp()) sum ++;
    }

    pos_list flag_list = b.find_rank(10, all_chess);

    if (flag_list.size() > 0)
    {
        int_type flag = flag_list[0];
        col_type flag_col = position(flag).col;

        extra_score(b, sum, belong_to, 3, flag_col, 65);
        extra_score(b, sum, belong_to, 4, flag_col, 90);
        extra_score(b, sum, belong_to, 5, flag_col + 1, 90);
        extra_score(b, sum, belong_to, 5, flag_col - 1, 90);
        extra_score(b, sum, belong_to, 2, 2, 40);
        extra_score(b, sum, belong_to, 3, 4 - flag_col, 10);
        extra_score(b, sum, belong_to, 4, flag_col + 1, 10);
        extra_score(b, sum, belong_to, 4, flag_col - 1, 10);

        extra_score(b, sum, belong_to, 1, 1, 3);
        extra_score(b, sum, belong_to, 1, 3, 3);
    }

    return sum;
}

//
move_type run_strategy0(board & b, country_type belong_to)
{
    pos_list whole_list = b.find(belong_to);
    float max_value = -10000;
    float ratio = (score_0(39) + score_0(38))/(2 * score_0(40));
    move_type one_move;

    for_int(i, whole_list.size())
    {
        int_type s_code = whole_list[i];
        position s_pos(s_code);

        chess_type s_chess = b.find_chess(s_code);

        if (s_chess.movable() && !s_pos.is_base())
        {
            loop(d_code)
            {
                position d_pos(d_code);
                chess_type d_chess = b.find_chess(d_code);

                pos_list move_list = route_list(b, s_chess, d_code);
                bool accessible = (move_list.size() > 1);

                bool go_able = (!b.is_occupied(d_code)) ||
                        (b.is_occupied(d_code) &&
                         is_enemy(d_chess.belong_to, s_chess.belong_to) &&
                         !d_pos.is_camp() &&
                         !(d_pos.is_base() && (d_chess.rank != 10)))
                        ;

                if (accessible && go_able)
                {
                    board b2 = b;

                    b2.remove_position(s_code);

                    if (!b2.is_occupied(d_code))
                        b2.occupy(d_pos, s_chess.rank, s_chess.belong_to, normal);
                    else
                        switch(beat_it(s_chess.rank, d_chess.rank))
                        {
                            case 1:
                                b2.remove_position(d_code);
                                b2.occupy(d_pos, s_chess.rank, s_chess.belong_to, normal);
                            break;
                            case 0:
                                b2.remove_position(d_code);
                            break;
                            case -1:
                            break;
                            default: ;
                        }

                    float value = calculate_value_0(b2, belong_to) +
                                  calculate_value_0(b2, ally_country(belong_to)) -
                                  calculate_value_0(b2, left_country(belong_to)) -
                                  calculate_value_0(b2, right_country(belong_to));

                    if (under_attack_0(b2, b2.find_chess(d_code)))

                        value -= ratio * score_0(s_chess.rank);

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

#endif // STRATEGY0_CPP
