#ifndef FLASHINGFITEM_H
#define FLASHINGFITEM_H
#include<flashingftransistor.h>
#include"qelem.h"
#include <QTimer>
#include <QPainter>
#include <QDebug>

class FlashingFtransistorItem : public QObject, public FlashingFtransistor, public QElem
{
Q_OBJECT

public:
    FlashingFtransistorItem();

    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    virtual void paint(QPainter *painter);
    virtual QRectF boundingRect() const;
    virtual unsigned int showID(){return FlashingFtransistor::showID();}
    virtual void expToSvg(std::ofstream &file){FlashingFtransistor::expToSvg(file);}
protected:
    virtual void timerEvent(QTimerEvent *event);
};

#endif // FLASHINGFITEM_H
