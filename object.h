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

};

//
class chess : public position
{
private:
    rank_type rank;
    country_type belong_to;
    state_type state;

};


#endif // OBJECT_H
