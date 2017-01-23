#ifndef OBJECT_H
#define OBJECT_H

#include "def.h"

//
#include <vector>
//

#define MAXPOS 129 // 4*row_num*col_num + 3*3

//
class position
{
public:
    country_type country;
    row_type row;
    col_type col;

    position(country_type, row_type, col_type);
    position(int code);

    int encode();

    bool is_camp();
    bool is_base();
    bool on_rail();
    bool valid();

};

//
class chess_type
{
public:
    rank_type rank;
    country_type belong_to;
    state_type state;

    int code;

    chess_type();
    void set_empty(int c);
    bool is_labor();
    bool is_flag();
    bool movable();

};

//
typedef std::vector <int> pos_list;
//

class board
{
public:
    chess_type chesses[MAXPOS];

    board();
    void occupy(chess_type, position);
    void delete_position(position);
    bool is_occupied(position);
    void delete_belong_to(country_type); // according to belong_to
    bool is_empty(country_type); // according to belong_to

    pos_list find(state_type);
    pos_list find(rank_type);
    pos_list find(country_type); // according to belong_to
    pos_list find_allies(country_type); // according to belong_to
    pos_list find_country(country_type);


};


#endif // OBJECT_H
