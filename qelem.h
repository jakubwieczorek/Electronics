#ifndef QELEM_H
#define QELEM_H
#include<element.h>
#include<QGraphicsItem>
#include <QPainter>
#include <QDebug>
#include "qelem.h"

class QElem: virtual public Element, virtual public QGraphicsItem
{
public:
    QElem();
    virtual unsigned int showID(){}
    virtual void expToSvg(std::ofstream &file){}

    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    virtual QRectF boundingRect() const;

    void setBacklight(bool isBacklighted){backlight = isBacklighted;}
    bool getBacklight(){return backlight;}
    void setBacklightRect(QRectF backlightRect){this->backlightRect = backlightRect;}
    QRectF getBacklightRect(){return backlightRect;}

private:
    bool backlight;
    QRectF backlightRect;
};

#endif // QELEM_H
