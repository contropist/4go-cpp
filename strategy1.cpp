#ifndef STRATEGY1_CPP
#define STRATEGY1_CPP

//
#include "def.h"
#include "strategy1.h"
#include "route.h"
//

namespace strategy1 {

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
 float calculate_value(board & b, country_type belong_to)
 {
     pos_list all_chess = b.find_belong_to(belong_to);
     float sum = 0;

     if (b.is_empty(belong_to)) return 0;

     for_int(i, all_chess.size())
     {
         int_type pos = all_chess[i];

         chess_type chess = b.find_chess(pos);

         sum += score(chess.rank);

         sum += ratio * under_attack(b, chess);
     }

     return sum;
 }

 //
 float calculate_position_value(board & b, country_type belong_to)
 {
     pos_list all_chess = b.find_belong_to(belong_to);
     float sum = 0;
     col_type flag_col;

     if (b.is_empty(belong_to)) return 0;

     if (b.find_chess(position(belong_to, 5, 1)).is_flag())

         flag_col = 1;

     else if (b.find_chess(position(belong_to, 5, 3)).is_flag())

         flag_col = 3;

     else

         flag_col = 0;

     pos_list my_all_chess = b.find_country(belong_to);

     for_int(i, my_all_chess.size())
     {
         int_type my_pos = my_all_chess[i];

         chess_type my_chess = b.find_chess(my_pos);

         if (my_chess.state != empty)
         {
             float sign = (is_enemy(my_chess.belong_to, belong_to))?-1:2/5;

             sum += sign/10 * position_score(my_chess.rank) *
                              position_value(position(my_pos), flag_col);
         }

     }

     return sum;

 }



//
//
move_type run_strategy(board & b, country_type belong_to)
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

                        value = calculate_value(b2, belong_to)
                              + calculate_position_value(b2, belong_to)
                              + calculate_value(b2, ally_country(belong_to))
                              - calculate_value(b2, right_country(belong_to))
                              - calculate_value(b2, left_country(belong_to));

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

} // namespace strategy1
//

#endif // STRATEGY1_CPP
