#ifndef DRAWCHESS_H
#define DRAWCHESS_H

#include "object.h"

#include <QPainter>

void draw_all_chesses(board &, QPainter *);

void draw_chess(QPainter * paint, chess_type c);

void draw_extra(QPainter * paint, country_type belong_to, QString text, state_type state);


#endif // DRAWCHESS_H
