#ifndef MYSQUARE_H
#define MYSQUARE_H
#include <QGraphicsItem>
#include <QPainter>
#include <QDebug>

class MySquare : public QGraphicsItem
{
public:
    MySquare();
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    virtual QRectF boundingRect() const;
};

#endif // MYSQUARE_H
