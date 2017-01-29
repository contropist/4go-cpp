#ifndef OBJECT_H
#define OBJECT_H

#include "def.h"

//
#include <vector>
#include <QPainter>
//


//
class position
{
public:
    country_type country;
    row_type row;
    col_type col;

    position(country_type, row_type, col_type);
    position(int_type code);

    int_type encode();

    bool is_camp();
    bool is_base();
    bool on_rail();

};

//
class chess_type
{
public:
    rank_type rank;
    country_type belong_to;
    state_type state;

    int_type code;

    chess_type();
    chess_type(rank_type, country_type, state_type, int_type);
    void set_empty(int c);
    bool is_labor();
    bool is_flag();
    bool movable();

};

//
typedef std::vector <int_type> pos_list;
//

class board
{
private:
    chess_type chesses[MAXPOS];

public:
    country_type which_turn;

    board();
    void init_board();
    bool forbidden(rank_type, country_type, row_type, col_type);

    void occupy(int_type, rank_type, country_type, state_type);
    void occupy(position, rank_type, country_type, state_type);
    void remove_position(int_type);
    void remove_position(position);
    void change_state(int_type, state_type);
    void change_state(position, state_type);
    bool is_occupied(int_type);
    bool is_occupied(position);
    void delete_belong_to(country_type); // according to belong_to
    bool is_empty(country_type); // according to belong_to

    pos_list find(state_type);
    pos_list find(rank_type);
    pos_list find(country_type); // according to belong_to
    pos_list find_allies(country_type); // according to belong_to
    pos_list find_country(country_type);
    chess_type find_chess(int_type);
    chess_type find_chess(position);

};


#endif // OBJECT_H
