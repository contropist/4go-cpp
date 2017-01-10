#ifndef UTILS_CPP
#define UTILS_CPP

//
#include "utils.h"

//
int row_num(country_type country)
{
    return (country == middle)? 3:6;
}

int col_num(country_type country)
{
    return (country == middle)? 3:5;
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


#endif // UTILS_CPP
