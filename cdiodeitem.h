#ifndef MYSQUARE_H
#define MYSQUARE_H
#include <QGraphicsItem>
#include <QPainter>
#include <QDebug>
#include "qelem.h"
#include <cdiode.h>

class CdiodeItem : public QGraphicsItem, public Cdiode
{
public:
    CdiodeItem();

    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    virtual QRectF boundingRect() const;
    //virtual unsigned int showID(){Cdiode::showID();}
    //virtual void expToSvg(std::ofstream &file){Cdiode::expToSvg(file);}
};

#endif
