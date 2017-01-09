#include <QApplication>
#include <QPainter>
#include <QWidget>

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

    paint->drawRect(20, 20, 160, 160);
    paint->end();
}

MyMainWindow::MyMainWindow(QWidget *parent):QWidget(parent)
{
    setGeometry(100, 100, 200, 200);
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
