#ifndef OBJECT_CPP
#define OBJECT_CPP

#include "object.h"
#include "utils.h"

//
// position
//
position::position(country_type c, row_type r, col_type cl)
{
    if (country != null)
        country = c;
    else
        throw("Wrong country name");


    if ( (row >= 0) && (row < row_num(country)) )
       row = r;
    else
       throw("Wrong row number"); // error


    if ( (col >= 0) && (col < col_num(country)) )
       col = cl;
    else
       throw("Wrong col number"); // error
}

bool position::is_camp()
{
    return ( (country != middle) &&
             (row >= 1) &&
             (row <= 3) &&
             ( (row == col) || (row + col == 4) )
           );
}

bool position::is_base()
{
    return ( (country != middle) &&
             (row == 5) &&
             ( (col == 1) || (col == 3) )
           );
}

bool position::on_rail()
{
    return ( (country == middle) ||
             (row == 0) ||
             (row == 4) ||
             ( (row < 5) && ( (col == 0) || (col == 4) ) )
           );
}

bool position::valid()
{
    return ( (row >= 0) &&
             (row < (row_num(country))) &&
             (col >= 0) &&
             (col < (col_num(country)))
           );
}

//
// chess
//
bool chess::is_labor()
{
    return (rank == 30);
}

bool chess::is_flag()
{
    return (rank == 10);
}

bool chess::movable()
{
    return (!
            ( (rank == 10) || (rank == 100) )
           );
}

//
// board
//
board::board()
{
    occupied_list = NULL;
}


void board::occupy(chess c)
{

   chess new_c = c;

   chesses *new_ptr = new chesses;

   new_ptr->item = &new_c;
   new_ptr->next = occupied_list;

   occupied_list = new_ptr;

}


/*
void board::delete_position(position p)
{
    //
    return;
}

bool board::occupied(position p)
{
    //
    return true;
}

void board::delete_country(country_type belong_to);
{
    //
    return;
}

bool board::is_empty(country_type belong_to);
{
    //
    return false;
}
*/

chesses *board::find(state_type s)
{
   chesses *ptr = occupied_list;
   chesses *found = NULL;

   while (ptr)
   {
      if (ptr->item->state == s)
      {
          chesses *new_found = new chesses;

          new_found->item = ptr->item;
          new_found->next = found;
          found = new_found;
      }

      ptr = ptr->next;
   }

   return found;
}

chesses *board::find(rank_type r)
{
   chesses *ptr = occupied_list;
   chesses *found = NULL;

   while (ptr)
   {
      if (ptr->item->rank == r)
      {
          chesses *new_found = new chesses;

          new_found->item = ptr->item;
          new_found->next = found;
          found = new_found;
      }

      ptr = ptr->next;
   }

   return found;
}

chesses *board::find(country_type bt)
{
   chesses *ptr = occupied_list;
   chesses *found = NULL;

   while (ptr)
   {
      if (ptr->item->belong_to == bt)
      {
          chesses *new_found = new chesses;

          new_found->item = ptr->item;
          new_found->next = found;
          found = new_found;
      }

      ptr = ptr->next;
   }

   return found;
}

chesses *board::find_country(country_type c)
{
   chesses *ptr = occupied_list;
   chesses *found = NULL;

   while (ptr)
   {
      if (ptr->item->country == c)
      {
          chesses *new_found = new chesses;

          new_found->item = ptr->item;
          new_found->next = found;
          found = new_found;
      }

      ptr = ptr->next;
   }

   return found;
}

chesses *board::find(position *p)
{
   chesses *ptr = occupied_list;
   chesses *found = NULL;

   while (ptr)
   {
      if ( (ptr->item->country == p->country) &&
           (ptr->item->row == p->row) &&
           (ptr->item->col == p->col)
         )
      {
          chesses *new_found = new chesses;

          new_found->item = ptr->item;
          new_found->next = found;
          found = new_found;
      }

      ptr = ptr->next;
   }

   return found;
}





#endif // OBJECT_CPP
