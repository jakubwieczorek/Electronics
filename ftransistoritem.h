#ifndef FTRANSISTORITEM_H
#define FTRANSISTORITEM_H
#include <QGraphicsItem>
#include <QPainter>
#include <QDebug>
#include <ftransistor.h>
#include "qelem.h"

class FtransistorItem : public Ftransistor, public QElem
{
public:
    FtransistorItem();
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    virtual void paint(QPainter *painter);
    virtual QRectF boundingRect() const;
    virtual unsigned int showID(){Ftransistor::showID();}
    virtual void expToSvg(std::ofstream &file){Ftransistor::expToSvg(file);}

};

#endif // FTRANSISTORITEM_H
