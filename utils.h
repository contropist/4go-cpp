#ifndef UTILS_H
#define UTILS_H

#include "object.h"

#include <QPainter>

void draw_chess(QPainter * paint,
                position p,
                char * text,
                chess_type c);

#endif // UTILS_H
