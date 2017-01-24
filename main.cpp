#include "main.h"
#include "parameter.h"
#include "object.h"
#include "def.h"
#include "draw-board.h"

#include <QApplication>
#include <QPainter>
#include <QRectF>

board b;

void MyMainWindow::paintEvent(QPaintEvent *)
{

    paint = new QPainter;

    paint->begin(this);

//    paint->drawText(QRectF(QPointF(150, 150), QSizeF(30, 30)),
//                    Qt::AlignCenter, "军长");

    redraw(paint);

    paint->end();



}

MyMainWindow::MyMainWindow(QWidget *parent):QWidget(parent)
{
    setGeometry(40, 40, frame_size, frame_size);
    // setWindowTitle("米勒酷四国军棋");

    setWindowTitle("米勒酷四国军棋");

    b.occupy(position(up, 4, 1), 38, up, normal);
    b.occupy(position(down, 1, 2), 33, left, normal);
    b.occupy(position(right, 3, 2), 40, down, normal);
    b.occupy(position(left, 1, 4), 39, right, normal);
    b.occupy(position(middle, 0, 0), 30, down, normal);


}

MyMainWindow::~MyMainWindow()
{
    delete paint;
}

//
void redraw(QPainter * paint)
{
    draw_board(paint);
    b.draw_all_chesses(paint);
}


//
int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    MyMainWindow w;

    w.show();

    return a.exec();
}
