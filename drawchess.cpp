#ifndef DRAWCHESS_CPP
#define DRAWCHESS_CPP

#include "drawchess.h"
#include "def.h"
#include "parameter.h"

//
void draw_all_chesses(board & b, QPainter * paint)
{
    loop(i)
    {
        if (b.is_occupied(i))
            draw_chess(paint, b.find_chess(i));
    }

}

//
void draw_chess(QPainter * paint, position p, country_type belong_to, QString text, state_type state)
{

    structxy xy = get_top_left_corner(p);
    structxy ab = get_size_xy(p.country);
    float iota = 0.1; // small offset

    QColor color;

    switch (belong_to)
    {
        case down:  color = Qt::red;     break;
        case right: color = Qt::yellow;  break;
        case up:    color = QColor(250, 100, 250); break;
        case left:  color = Qt::green;   break;
        default:    color = Qt::lightGray;
    }

    if (state == picked_up)
        color = Qt::lightGray;

    Qt::BrushStyle filled_style = Qt::SolidPattern;
    if (state == extra)
        filled_style = Qt::DiagCrossPattern;

    paint->setBrush(QBrush(color, filled_style));
    paint->drawRoundRect(QRectF(QPointF(xy.x, xy.y), QSizeF(ab.x, ab.y)),
                           corner, corner);

    paint->setFont(QFont("Times", lsize*0.57));

    switch (p.country)
    {
        case left:
                paint->save();
                paint->rotate(90);
                paint->drawText(QRectF(QPointF(xy.y, -xy.x - ab.x), QSizeF(ab.y, ab.x)),
                                Qt::AlignCenter, text);
                paint->restore();
                break;
        case right:
                paint->save();
                paint->rotate(-90);
                paint->drawText(QRectF(QPointF(-xy.y - ab.y, xy.x + iota * ab.x), QSizeF(ab.y, ab.x)),
                                Qt::AlignCenter, text);
                paint->restore();
                break;
        case up:
        case down:
        case middle:
                paint->drawText(QRectF(QPointF(xy.x, xy.y), QSizeF(ab.x, ab.y)),
                                Qt::AlignCenter, text); break;
        default: ;
    }
}

void draw_chess(QPainter * paint, chess_type c)
{
    draw_chess(paint, position(c.code), c.belong_to, rank_code(c.rank), c.state);
}


//
void draw_extra(QPainter * paint, country_type belong_to, QString text, state_type state)
{
    draw_chess(paint, position(belong_to, 5, 5), belong_to, text, state);
}


//

#endif // DRAWCHESS_CPP
