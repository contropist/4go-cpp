#ifndef DEF_H
#define DEF_H

#include <QString>

#define NORANK -100

//
// new types
//

typedef enum {
    down,
    right,
    up,
    left,
    middle,
    null // error
} country_type;

typedef enum {
    normal,
    picked_up,
    hidden,
    extra,
    empty
} state_type;

typedef int row_type; // 0, 1, 2, 3, 4, 5
typedef int col_type; // 0, 1, 2, 3, 4
typedef int rank_type; // 40, 39, 38, 37, 36, 35, 34, 33, 30, 100, 10, 0, NORANK

//
// functions
//
int row_num(country_type);
int col_num(country_type);

country_type right_country(country_type);
country_type left_country(country_type);
country_type ally(country_type);

country_type operator ++ (country_type &, int); // country ++;
country_type operator -- (country_type &, int); // country --;

country_type operator ++ (country_type &); // ++ country;
country_type operator -- (country_type &); // -- country;

QString rank_code(rank_type);



#endif // DEF_H
