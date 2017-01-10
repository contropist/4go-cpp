#ifndef OBJECT_H
#define OBJECT_H

typedef enum {
    up,
    left,
    down,
    right,
    middle
} country_type;

typedef enum {
    normal,
    picked_up,
    hidden,
    extra,
} state_type;

typedef enum {
    command_officer = 40,
    general = 39,
    division_leader = 38,
    brigadier = 37,
    colonel = 36,
    lieutenant_colonel = 35,
    captain = 34,
    platoon_leader = 33,
    combat_engineer = 30,
    flag = 10,
    mine = 100,
    bomb = 0
} rank_type;

//
class position
{
private:
    country_type country;
    int row;
    int col;

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
