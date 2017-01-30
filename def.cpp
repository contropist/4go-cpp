#ifndef DEF_CPP
#define DEF_CPP

//
#include "def.h"

//
row_type row_num(country_type country)
{
    return (country == middle)? 3:6;
}

col_type col_num(country_type country)
{
    return (country == middle)? 3:5;
}

bool valid_position(country_type country, row_type row, col_type col)
{
    return ( (country != null) &&
             (row >= 0) &&
             (col >= 0) &&
             (row < row_num(country)) &&
             (col < col_num(country))
           );
}



//
country_type right_country(country_type country)
{
    switch (country)
    {
       case down:  return right; break;
       case right: return up;    break;
       case up:    return left;  break;
       case left:  return down;  break;        
       default: // error
          throw("Wrong country in calling right_country");

    }
}

//
country_type left_country(country_type country)
{
    switch (country)
    {
       case down:  return left;  break;
       case right: return down;  break;
       case up:    return right; break;
       case left:  return up;    break;
       default: // error
          throw("Wrong country in calling left_country");

    }
}

//
country_type right_country(country_type country, unsigned int i)
{
    if (i == 0)
        return country;
    else if (i > 0)
        return right_country(right_country(country), i - 1);
    else
        throw("Wrong argument in right_country");
}

//
country_type left_country(country_type country, unsigned int i)
{
    if (i == 0)
        return country;
    else if (i > 1)
        return left_country(left_country(country), i - 1);
    else
        throw("Wrong argument in left_country");
}

//
country_type ally_country(country_type country)
{
    return right_country(country, 2);
}

//
bool is_enemy(country_type country1, country_type country2)
{
    if ((country1 == middle) || (country2 == middle))
        return false;

    if ((country2 == left_country(country1)) ||
        (country2 == right_country(country1)))
        return true;
    else
        return false;
}

//
country_type operator ++ (country_type & country, int) // country ++
{
    country_type temp_country = country;
    country = right_country(country);

    return temp_country;
}

//
country_type operator ++ (country_type & country) // ++ country
{
    country = right_country(country);
    return country;
}

//
QString rank_code(rank_type rank)
{
    switch (rank)
    {
       case 40:  return "司令"; break;
       case 39:  return "军长"; break;
       case 38:  return "师长"; break;
       case 37:  return "旅长"; break;
       case 36:  return "团长"; break;
       case 35:  return "营长"; break;
       case 34:  return "连长"; break;
       case 33:  return "排长"; break;
       case 30:  return "工兵"; break;
       case 10:  return "军旗"; break;
       case 100: return "地雷"; break;
       case 0:   return "炸弹"; break;
       default:  throw("Wrong rank number"); // error
    };
}

//
// win = 1, lose = -1, equal = 0
int beat_it(rank_type rank1, rank_type rank2)
{
    if ((rank1 == NORANK) || (rank2 == NORANK))
        throw("Wrong rank in comparison when fighting");
    else if (rank1 * rank2 == 0) // if either is bomb then equal
        return 0;
    else if ((rank1 == 30) && (rank2 == 100)) // laborer > landmine
        return 1;
    else if ((rank1 == 100) && (rank2 == 30)) // landmine < laborer
        return -1;
    else
        if (rank1 > rank2)
            return 1;
        else if (rank1 < rank2)
            return -1;
        else
            return 0;

}


#endif // DEF_CPP
