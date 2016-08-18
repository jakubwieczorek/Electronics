#ifndef MYGRAPHICSVIEW_H
#define MYGRAPHICSVIEW_H
#include <QGraphicsView>

class MyGraphicsView : public QGraphicsView
{
    Q_OBJECT

public:
    MyGraphicsView(QWidget *widget);
};

#endif // MYGRAPHICSVIEW_H
