#ifndef DEF_H
#define DEF_H

#include <QString>

#define NORANK 10000
#define NOPOSITION 15000

// macros
#define MAXPOS  129 // 4*row_num*col_num + 3*3
#define MAXPOS0 120 // 4*row_num*col_num, without middle

#define loop(i)  for (int_type i = 0; i < MAXPOS;  i ++)
#define loop0(i) for (int_type i = 0; i < MAXPOS0; i ++) // without middle country
//


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

typedef unsigned int row_type; // 0, 1, 2, 3, 4, 5
typedef unsigned int col_type; // 0, 1, 2, 3, 4
typedef unsigned int rank_type; // 40, 39, 38, 37, 36, 35, 34, 33, 30, 100, 10, 0, NORANK
typedef unsigned int int_type; // 0..MAXPOS, NOPOSITION = position_type

//
// functions
//
row_type row_num(country_type);
col_type col_num(country_type);

country_type right_country(country_type);
country_type  left_country(country_type);

country_type right_country(country_type, unsigned int); // country + 1, country + 2
country_type  left_country(country_type, unsigned int); // country - 1, country - 2

country_type operator ++ (country_type &, int); // country ++;
country_type operator ++ (country_type &); // ++ country;

QString rank_code(rank_type);
int beat_it(rank_type, rank_type);

#endif // DEF_H
