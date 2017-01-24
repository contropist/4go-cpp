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
    void mousePressEvent(QMouseEvent *);

//    QImage * image;
    QPainter * paint;

};

//
void redraw(QPainter *);
void click_pos(int);


#endif // MAIN_H
