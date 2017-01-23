#ifndef OBJECT_H
#define OBJECT_H

#include "utils.h"

//
#include <vector>
//

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

typedef std::vector <chess> chesses;

//
class board
{
public:
    chesses * occupied_list;

    board();
    void occupy(chess);
    void delete_position(position);
    bool is_occupied(position);
    void delete_country(country_type); // according to belong_to
    bool is_empty(country_type); // according to belong_to

    chesses * find(state_type);
    chesses * find(rank_type);
    chesses * find(country_type); // according to belong_to
    chesses * find_country(country_type);
    chesses * find(position*);


};


#endif // OBJECT_H
