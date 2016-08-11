#ifndef MYSQUARE_H
#define MYSQUARE_H
#include <QGraphicsItem>
#include <QPainter>
#include <QDebug>
#include <cdiode.h>
#include "qelem.h"

class CdiodeItem : public QGraphicsItem, public Cdiode, public QElem
{
public:
    CdiodeItem();
/*
    using Cdiode::getSpin;

    using Cdiode::getInteriorRed;
    using Cdiode::getInteriorGreen;
    using Cdiode::getInteriorBlue;

    using Cdiode::getLineRed;
    using Cdiode::getLineGreen;
    using Cdiode::getLineBlue;

    using Cdiode::setSpin;

    using Cdiode::setInteriorRed;
    using Cdiode::setInteriorGreen;
    using Cdiode::setInteriorBlue;

    using Cdiode::setLineRed;
    using Cdiode::setLineGreen;
    using Cdiode::setLineBlue;
*/
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    virtual QRectF boundingRect() const;
    virtual unsigned int showID(){Cdiode::showID();}
    virtual void expToSvg(std::ofstream &file){Cdiode::expToSvg(file);}
};

#endif
