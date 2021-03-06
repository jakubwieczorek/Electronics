#ifndef MYSQUARE_H
#define MYSQUARE_H
#include <QGraphicsItem>
#include <QPainter>
#include <QDebug>
#include <cdiode.h>
#include "qelem.h"

class CdiodeItem : public QObject, public Cdiode, public QElem
{
    Q_OBJECT

public:
    CdiodeItem();

    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    virtual void paint(QPainter *painter);
    virtual QRectF boundingRect() const;
    virtual unsigned int showID(){return Cdiode::showID();}
    virtual void expToSvg(std::ofstream &file){Cdiode::expToSvg(file);}
};

#endif
