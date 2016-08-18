#ifndef MYGRAPHICSVIEW_H
#define MYGRAPHICSVIEW_H
#include <QGraphicsView>

class MyGraphicsView : public QGraphicsView
{
    Q_OBJECT

public:
    MyGraphicsView(QWidget *widget);
//private slots:
    //virtual void mouseMoveEvent(QMouseEvent *event);
};

#endif // MYGRAPHICSVIEW_H
