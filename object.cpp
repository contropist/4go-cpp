#ifndef OBJECT_CPP
#define OBJECT_CPP

#include "object.h"
#include "utils.h"

//

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

#endif // OBJECT_CPP
