#ifndef MYSQUARE_H
#define MYSQUARE_H
#include <QGraphicsItem>
#include <QPainter>
#include <QDebug>
#include <cdiode.h>
#include "qelem.h"

class CdiodeItem : public Cdiode, public QElem
{
public:
    CdiodeItem();

    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    virtual void paint(QPainter *painter);
    virtual QRectF boundingRect() const;
    virtual unsigned int showID(){Cdiode::showID();}
    virtual void expToSvg(std::ofstream &file){Cdiode::expToSvg(file);}
};

#endif
