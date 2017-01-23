#ifndef MAIN_H
#define MAIN_H

//
#include <QWidget>
//


//
class MyMainWindow: public QWidget
{

public:
    MyMainWindow(QWidget * parent = 0);
    ~MyMainWindow();

private:
    void paintEvent(QPaintEvent *);
//    QImage * image;
    QPainter * paint;
};

//
void redraw(QPainter *);


#endif // MAIN_H
