#ifndef UTILS_CPP
#define UTILS_CPP

#include "utils.h"
#include "parameter.h"

//
void draw_chess(QPainter * paint,
                chess_type c)
{
    position p(c.code);

    structxy xy = get_top_left_corner(p);
    structxy ab = get_size_xy(p.country);
    float iota = 0.1; // small offset

    QColor color;

    switch (c.belong_to)
    {
        case down:  color = Qt::red;     break;
        case right: color = Qt::yellow;  break;
        case up:    color = QColor(250, 100, 250); break;
        case left:  color = Qt::green;   break;
        default:    color = Qt::lightGray;
    }

    if (c.state == picked_up)
        color = Qt::lightGray;

    Qt::BrushStyle filled_style = Qt::SolidPattern;
    if (c.state == extra)
        filled_style = Qt::DiagCrossPattern;

    paint->setBrush(QBrush(color, filled_style));
    paint->drawRoundRect(QRectF(QPointF(xy.x, xy.y), QSizeF(ab.x, ab.y)),
                           corner, corner);

    QFont font;
    font.setPointSizeF(lsize*57/100);
    paint->setFont(font);

    switch (p.country)
    {
        case left:
                paint->save();
                paint->rotate(90.0);
                paint->drawText(xy.x, xy.y,
                            // QRectF(QPointF(xy.x, xy.y), QSizeF(ab.x, ab.y)),
                            // Qt::AlignCenter,
                                rank_code(c.rank));
                paint->restore();
                break;
        case right:
                paint->save();
                paint->rotate(-90.0);
                paint->drawText(QRectF(QPointF(xy.x, xy.y), QSizeF(ab.x, ab.y)),
                                Qt::AlignCenter, rank_code(c.rank));
                paint->restore();
                break;
        case up:
        case down:
        case middle:
                paint->drawText(QRectF(QPointF(xy.x, xy.y), QSizeF(ab.x, ab.y)),
                                Qt::AlignCenter, rank_code(c.rank)); break;
        default: ;
    }
}

#endif // UTILS_CPP
