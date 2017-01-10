#include "main.h"
#include "object.h"
#include "utils.h"

#include <QApplication>
#include <QPainter>
#include <QWidget>

//
class MyMainWindow: public QWidget
{

public:
    MyMainWindow(QWidget *parent = 0);
    ~MyMainWindow();

private:
    void paintEvent(QPaintEvent *);
    QPainter *paint;
};

void MyMainWindow::paintEvent(QPaintEvent *)
{
    paint = new QPainter;

    paint->begin(this);
    paint->setPen(QPen(Qt::blue, 4, Qt::DashLine));
    paint->setBrush(QBrush(Qt::red, Qt::SolidPattern));

    paint->drawRect(100, 100, 150, 150);

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

}

//
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MyMainWindow w;
    w.show();

    return a.exec();
}
