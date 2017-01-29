#ifndef MAIN_H
#define MAIN_H

#include "object.h"
#include "def.h"

//
#include <QWidget>
//

//
typedef enum {
    human,
    strategy0,
    strategy1

} player_type;


//
class MyMainWindow: public QWidget
{

private:
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *);

//    QImage * image;
    QPainter * paint;

    board b;


public:
    MyMainWindow(QWidget * parent = 0);
    ~MyMainWindow();

    void redraw();
    void click_pos(int_type);
    void draw_route(pos_list, rank_type, country_type, float);

    void go_to_next_country();
    void move_to(int_type, int_type);

};

//


#endif // MAIN_H
