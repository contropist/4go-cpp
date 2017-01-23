#ifndef DRAW_BOARD_CPP
#define DRAW_BOARD_CPP

#include "parameter.h"
#include "def.h"
#include "object.h"

#define corner 22 // corner size for draw rounded rectangle
//
#include <QPainter>
//

void draw_empty_chess(country_type, int, int, QPainter *);
void draw_board(QPainter *);
void draw_middle(QPainter *);

//
void draw_board(QPainter * paint)
{
    country_type country;
    int counter;

    for (country = down, counter = 0; counter < 4; country ++, counter ++)
        for (int row = 0; row < row_num(country); row ++)
             for (int col = 0; col < col_num(country); col ++)

                 draw_empty_chess(country, row, col, paint);

}

void draw_empty_chess(country_type country, row_type row, col_type col, QPainter * paint)
{

    structxy xy = get_top_left_corner(country, row, col);
    structxy ab = get_size_xy(country);
    structxy xy2 = coordinatexy(country, row, col, 1.0, 1.0/2);
    structxy xyn = coordinatexy(country, row, col+1, 0.0, 1.0/2);
    structxy xy3 = coordinatexy(country, row, col, 1.0/2, 1.0);
    structxy xyd = coordinatexy(country, row+1, col, 1.0/2, 0.0);
    structxy xy0 = coordinatexy(country, row, col, 1.0/2, 1.0/2);
    structxy xynew;


    position pos(country, row, col);

    paint->setPen(QPen(Qt::blue));

    if (pos.is_camp())
    {
        paint->setPen(QPen(Qt::white, 2)); // erase rectangle
        paint->setBrush(QBrush(Qt::white, Qt::SolidPattern));
        paint->drawRoundRect(QRectF(QPointF(xy.x, xy.y), QSizeF(ab.x, ab.y)), corner, corner);

        paint->setPen(QPen(Qt::blue, 2));

        for (int i = -1; i <= 1; i += 2)
            for (int j = -1; j <= 1; j += 2)
                if ((row != 2) || (col != 2))
                {
                    if ((row + i == 2) && (col + j == 2))
                        xynew = coordinatexy(country, row + i, col + j, 0.5-0.4*j, 0.5-0.4*i);
                    else
                        xynew = coordinatexy(country, row + i, col + j, 0.5-0.5*j, 0.5-0.5*i);

                    paint->drawLine(QPointF(xy0.x, xy0.y), QPointF(xynew.x, xynew.y));
                }

        paint->setPen(QPen(Qt::red, 2));

        paint->drawEllipse(QPointF(xy0.x, xy0.y), ab.x/2, ab.y/2);

    }
    else
    {
        if (pos.is_base())
            paint->setPen((QPen(Qt::red, 2)));
        else
            paint->setPen((QPen(Qt::blue, 2)));

        paint->setBrush(QBrush(Qt::white, Qt::SolidPattern));
        paint->drawRoundRect(QRectF(QPointF(xy.x, xy.y), QSizeF(ab.x, ab.y)), corner, corner);
        paint->setPen(QPen(Qt::blue, 2));
    }

    if (col < 4) paint->drawLine(QPointF(xy2.x, xy2.y), QPointF(xyn.x, xyn.y));
    if (row < 5) paint->drawLine(QPointF(xy3.x, xy3.y), QPointF(xyd.x, xyd.y));

}


void draw_middle(QPainter * paint)
{

    paint->setPen(QPen(Qt::blue, 2));

    structxy xyup, xydown, xyleft, xyright;

    for (int j = 0; j <= 4; j += 2)
    {
        xyup = coordinatexy(up, 0, j, 1.0/2, 0.0);
        xydown = coordinatexy(down, 0, 4-j, 1.0/2, 0.0);
        xyleft = coordinatexy(left, 0, j, 1.0/2, 0.0);
        xyright = coordinatexy(right, 0, 4-j, 1.0/2, 0.0);

        paint->drawLine(QPointF(xyup.x, xyup.y), QPointF(xydown.x, xydown.y));
        paint->drawLine(QPointF(xyleft.x, xyleft.y), QPointF(xyright.x, xyright.y));
    }

    // draw trails
    structxy leftp =  coordinatexy(left,  0, 0, 1.0/2, 0.0);
    structxy leftq =  coordinatexy(left,  0, 4, 1.0/2, 0.0);
    structxy downp =  coordinatexy(down,  0, 0, 1.0/2, 0.0);
    structxy downq =  coordinatexy(down,  0, 4, 1.0/2, 0.0);
    structxy rightp = coordinatexy(right, 0, 0, 1.0/2, 0.0);
    structxy rightq = coordinatexy(right, 0, 4, 1.0/2, 0.0);
    structxy upp =    coordinatexy(up,    0, 0, 1.0/2, 0.0);
    structxy upq =    coordinatexy(up,    0, 4, 1.0/2, 0.0);

    paint->setPen(QPen(Qt::blue, 2, Qt::DashLine));
    paint->drawLine(QPointF(leftq.x,  leftq.y),  QPointF(downp.x,  downp.y));
    paint->drawLine(QPointF(downq.x,  downq.y),  QPointF(rightp.x, rightp.y));
    paint->drawLine(QPointF(rightq.x, rightq.y), QPointF(upp.x,    upp.y));
    paint->drawLine(QPointF(upq.x,    upq.y),    QPointF(leftp.x,  leftp.y));

    // draw squares
    float radius;

    paint->setPen(QPen(Qt::blue, 2));
    for (int i = 0; i <= 4; i += 2)
        for (int j = 0; j <= 4; j += 2)
        {
            xyup =   coordinatexy(up,   0, i, 1.0/2, 0.0);
            xyleft = coordinatexy(left, 0, j, 1.0/2, 0.0);
            radius = lsize*0.8;

            paint->drawRoundRect(QRectF(QPointF(xyup.x - radius, xyleft.y - radius),
                                         QSizeF(2*radius, 2*radius)), corner, corner);
        }

}

//
void draw_chess_board(QPainter * paint)
{
    draw_board(paint);
    draw_middle(paint);

}

#endif // DRAW_BOARD_CPP
