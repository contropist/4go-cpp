#include "main.h"
#include "parameter.h"
#include "object.h"
#include "utils.h"
#include "draw-board.h"

#include <QApplication>
#include <QPainter>
#include <QRectF>


void MyMainWindow::paintEvent(QPaintEvent *)
{

    paint = new QPainter;

    paint->begin(this);
//    paint->setPen(QPen(Qt::blue, 4, Qt::DashLine));
//    paint->setBrush(QBrush(Qt::red, Qt::SolidPattern));

//    paint->drawRect(100, 100, 150, 150);

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


}

MyMainWindow::~MyMainWindow()
{
    delete paint;
}


//
void draw_all_chesses(QPainter * paint)
{

    return;

}

//
void redraw(QPainter * paint)
{
    draw_chess_board(paint);
    draw_all_chesses(paint);
}


//
int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    MyMainWindow w;

    w.show();

    return a.exec();
}
