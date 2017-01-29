#include "main.h"
#include "parameter.h"
#include "object.h"
#include "def.h"
#include "drawboard.h"
#include "drawchess.h"
#include "utils.h"
#include "route.h"

#include <QApplication>
#include <QPainter>
#include <QRectF>
#include <QMouseEvent>
#include <QMessageBox>

#include <QTime>

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

bool board::forbidden(rank_type rank, country_type country, row_type row, col_type col)
{
    position p(country, row, col);

    if ((rank == 10) && !p.is_base())
        return true;

    if (p.is_base() && !((rank == 10) || (rank == 100) || (rank == 33)))
        return true;

    if ((rank == 100) && (row <= 3))
        return true;

    if ((rank == 0) && (row == 0))
        return true;

    if ((rank == 100) && (row == 4) && (col % 2 == 0))
    {
        rank_type its_rank = find_chess(position(country, 5, col)).rank;
        if ((its_rank == 40) || (its_rank == 39) || (its_rank == 38) || (its_rank == 0))
            return true;
    }

    if ((row == 5) && (col % 2 == 0) &&
        ((rank == 40) || (rank == 39) || (rank == 38) || (rank == 0)))
    {
        rank_type its_rank = find_chess(position(country, 4, col)).rank;
        if (its_rank == 100)
            return true;
    }

    return false;
}

void board::init_board()
{
    QTime time;
    time= QTime::currentTime();
    qsrand(time.msec()+time.second()*1000);

    country_type country;
    rank_type rank;
    row_type row;
    col_type col;

    for_country(belong_to, counter)
    {
        for_int(whole_rank_size, i)
        {
            country = belong_to;
            rank = whole_rank_set[i];

            do
            {
                row = qrand() % row_num(belong_to);
                col = qrand() % col_num(belong_to);

            } while (is_occupied(position(country, row, col)) ||
                     position(country, row, col).is_camp() ||
                     forbidden(rank, country, row, col));

            occupy(position(country, row, col), rank, belong_to, normal);

        }
    }

}

MyMainWindow::MyMainWindow(QWidget *parent):QWidget(parent)
{
    setGeometry(40, 40, frame_size, frame_size);
    // setWindowTitle("米勒酷四国军棋");

    setWindowTitle("米勒酷四国军棋");

    paint = new QPainter;

    b.init_board();

}

MyMainWindow::~MyMainWindow()
{
    delete paint;
}

//
void MyMainWindow::redraw()
{
    draw_board(paint);
    draw_all_chesses(b, paint);
}

//
void MyMainWindow::draw_route(pos_list move_list,
                              rank_type rank, country_type belong_to,
                              float time = 0.1)
{
    size_t len = move_list.size();
    for(size_t i = 0; i < len; i ++)
    {
        int_type pos = move_list[i];
        b.remove_position(pos);
        b.occupy(pos, rank, belong_to, picked_up);
        repaint();

        // sleep for some time
        QTime t;
        t.start();
        while (t.elapsed() < 1000*time/len);

        b.remove_position(pos);
    }
}

//
void MyMainWindow::click_pos(int_type position_code)
{

    if (position_code == NOPOSITION) return;

    position p(position_code);
    chess_type c = b.find_chess(p);

    int_type picked_pos;

    pos_list picked_list = b.find(picked_up);
    size_t len = picked_list.size();

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
       chess_type picked_chess = b.find_chess(picked_pos);

       pos_list move_list = route_list(b, picked_chess, position_code);
       bool accessible = (move_list.size() > 1);

       if (!accessible)
       {
            b.change_state(picked_pos, normal);
       }

       if (accessible && (c.state == empty)) // empty position
       {
            draw_route(move_list, picked_chess.rank, picked_chess.belong_to);

            b.occupy(p, picked_chess.rank, picked_chess.belong_to, normal);

       }

       if (accessible && (c.state != empty) &&
           is_enemy(c.belong_to, picked_chess.belong_to) &&
           (!p.is_camp())) // fight with it!
       {
            int beat = beat_it(picked_chess.rank, c.rank);

            draw_route(move_list, picked_chess.rank, picked_chess.belong_to);

            if (beat >= 0)
            {
                b.remove_position(p);
                if (c.is_flag()) b.delete_belong_to(c.belong_to);
            }

            if (beat == -1)
                b.occupy(p, c.rank, c.belong_to, normal);

            if (beat == 1)
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
