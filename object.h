#ifndef OBJECT_H
#define OBJECT_H

#include "utils.h"

//
class position
{
public:
    country_type country;
    row_type row;
    col_type col;

    position(country_type, row_type, col_type);

    bool is_camp();
    bool is_base();
    bool on_rail();
    bool valid();

};

//
class chess : public position
{
public:
    rank_type rank;
    country_type belong_to;
    state_type state;

    bool is_labor();
    bool is_flag();
    bool movable();

};

typedef struct chess_list {

    //
    // Here really subtle issue whether to use
    //      (chess) or (chess *) for declaring item
    // have to be very careful
    //      (chess) is to copy the object
    //      (chess *) is only copy the pointer
    // if here thing gets changed,
    //      the codes in other files have to change too

    // chess item; // to copy the object
    chess *item; // to copy the pointer

    chess_list *next;

} chesses;

//
class board
{
public:
    chesses *occupied_list;

    board();
    void occupy(chess);
    void delete_position(position);
    bool occupied(position);
    void delete_country(country_type); // according to belong_to
    bool is_empty(country_type); // according to belong_to

    chesses *find(state_type);
    chesses *find(rank_type);
    chesses *find(country_type); // according to belong_to
    chesses *find_country(country_type);
    chesses *find(position*);


};


#endif // OBJECT_H
