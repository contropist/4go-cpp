#ifndef OBJECT_H
#define OBJECT_H

#include "utils.h"

//
class position
{
private:
    country_type country;
    row_type row;
    col_type col;

public:
    position(country_type, row_type, col_type);
    bool is_camp();
    bool is_base();
    bool on_rail();
    bool valid();

};

//
class chess : public position
{
private:
    rank_type rank;
    country_type belong_to;
    state_type state;

public:
//    chess();
    bool is_labor();
    bool is_flag();
    bool movable();

};

//
class board
{
private:
    chess *occupied_list;

public:
    board();
    void occupy(chess);
    void delete_position(position);
    bool occupied(position);
    void delete_country(country_type); // according to belong_to
    bool is_empty(country_type); // according to belong_to

    chess find_picked_up();
    chess find_country(country_type);
    chess find_whole_chess(position);
    chess find_belong_to(country_type); // according to belong_to
    chess find_rank(rank_type);
    rank_type find_its_rank(position);


};


#endif // OBJECT_H
