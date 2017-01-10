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
    bool is_labor();
    bool is_flag();
    bool movable();

};


#endif // OBJECT_H
