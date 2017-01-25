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
        int position_code = search_xy(event->x(), event->y());
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
void MyMainWindow::click_pos(int position_code)
{

    position p(position_code);

    if (b.is_occupied(p))
        b.remove_position(p);
    else
        b.occupy(p, 40, down, picked_up);

    ;

}


//
int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    MyMainWindow w;

    w.show();

    return a.exec();
}
