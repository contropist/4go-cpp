#include "main.h"
#include "parameter.h"
#include "object.h"
#include "def.h"
#include "drawboard.h"
#include "drawchess.h"
#include "utils.h"

#include <QApplication>
#include <QPainter>
#include <QRectF>
#include <QMouseEvent>

void MyMainWindow::paintEvent(QPaintEvent *)
{

    paint->begin(this);
    redraw();
    paint->end();
}

void MyMainWindow::mousePressEvent(QMouseEvent * event)
{
    if (event->button() == Qt::LeftButton)
    {
        int_type position_code = search_xy(event->x(), event->y());
        if (position_code != NOPOSITION)
        {
            click_pos(position_code);
            repaint();
        }
    }
}

MyMainWindow::MyMainWindow(QWidget *parent):QWidget(parent)
{
    setGeometry(40, 40, frame_size, frame_size);
    // setWindowTitle("米勒酷四国军棋");

    setWindowTitle("米勒酷四国军棋");

    paint = new QPainter;

    b.occupy(position(up, 4, 1), 38, up, normal);
    b.occupy(position(down, 1, 2), 33, left, normal);
    b.occupy(position(right, 3, 2), 39, down, normal);
    b.occupy(position(left, 1, 4), 40, right, normal);
    b.occupy(position(middle, 0, 0), 30, down, normal);


}

MyMainWindow::~MyMainWindow()
{
    delete paint;
}

//
void MyMainWindow::redraw()
{
    draw_board(paint);
    b.draw_all_chesses(paint);
}

//
void MyMainWindow::click_pos(int_type position_code)
{

    if (position_code == NOPOSITION) return;

    position p(position_code);
    chess_type c = b.find_chess(p);

    int_type picked_pos;

    pos_list picked_list = b.find(picked_up);
    unsigned int len = picked_list.size();

    if (len > 1)
        throw("picked up more than one chess in click_pos()");
    else if (len == 1)
        picked_pos = picked_list[0];
    else
        picked_pos = NOPOSITION;

    if ((picked_pos == NOPOSITION) && (c.state != empty))
    //      (b.which_turn == c.belong_to) &&
        if ((c.movable()) && (!p.is_base()))
            b.change_state(p, picked_up);

    if (picked_pos != NOPOSITION) // nothing has been picked up
    {
       bool accessible = !b.is_occupied(p); // need to modify!
       chess_type picked_chess = b.find_chess(picked_pos);

       if (!accessible)
       {
            b.change_state(picked_pos, normal);
       }

       if (accessible && (c.state == empty)) // empty position
       {
           b.remove_position(picked_pos);
            // draw route
            // ...

            b.occupy(p, picked_chess.rank, picked_chess.belong_to, normal);

       }
    }

}


//
int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    MyMainWindow w;

    w.show();

    return a.exec();
}
