#ifndef FTRANSISTORITEM_H
#define FTRANSISTORITEM_H
#include <QGraphicsItem>
#include <QPainter>
#include <QDebug>
#include <ftransistor.h>

class FtransistorItem : public QGraphicsItem, public Ftransistor
{
public:
    FtransistorItem();
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    virtual QRectF boundingRect() const;
};

#endif // FTRANSISTORITEM_H
