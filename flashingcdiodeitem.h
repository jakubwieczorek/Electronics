#ifndef FLASHINGCDIODEITEM_H
#define FLASHINGCDIODEITEM_H
#include<flashingcdiode.h>
#include"qelem.h"
#include <QTimer>
#include <QPainter>
#include <QDebug>

class FlashingCdiodeItem : public QObject, public FlashingCdiode, public QElem
{
Q_OBJECT

public:
    FlashingCdiodeItem();

    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    virtual void paint(QPainter *painter);
    virtual QRectF boundingRect() const;
    virtual unsigned int showID(){FlashingCdiode::showID();}
    virtual void expToSvg(std::ofstream &file){FlashingCdiode::expToSvg(file);}
protected:
    virtual void timerEvent(QTimerEvent *event);

private:
    QTimer *timer;
};

#endif // FLASHINGCDIODEITEM_H
