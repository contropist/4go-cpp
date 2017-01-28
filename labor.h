#ifndef LABOR_H
#define LABOR_H

#include "object.h"

#include <vector>

//
typedef std::vector <pos_list> branches;
//

int_type nearest_middle(position p);

pos_list labor_fly_on_rail(board & b, int_type from_code, int_type to_code);
//

#endif // LABOR_H
