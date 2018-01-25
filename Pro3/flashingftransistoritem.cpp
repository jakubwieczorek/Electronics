#include "flashingftransistoritem.h"
#include <QTimerEvent>

FlashingFtransistorItem::FlashingFtransistorItem()
{
    setFlag(QGraphicsItem::ItemIsMovable);
    setFlag(QGraphicsItem::ItemIsSelectable);
    QElem::setBacklightRect(boundingRect());

    startTimer(1000);
}

void FlashingFtransistorItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    if(getBacklight())
        QElem::paint(painter, option, widget);

    this->paint(painter);
}

void FlashingFtransistorItem::paint(QPainter *painter)
{
    QColor penColor(getLineRed(), getLineGreen(), getLineBlue());
    QPen pen(penColor, 3.5);
    pen.setJoinStyle(Qt::MiterJoin);
    painter->setPen(pen);

    QColor brushColor(getInteriorRed(), getInteriorGreen(), getInteriorBlue());
    QBrush fillBrush;
    fillBrush.setColor(brushColor);
    fillBrush.setStyle(Qt::SolidPattern);

    painter->setBrush(fillBrush);
    painter->drawLine(QPointF(130, 45), QPointF(130,155));
    painter->drawEllipse(QPoint(100,100), 50, 50);
    painter->drawLine(QPointF(35, 100), QPointF(80,100));
    painter->drawLine(QPointF(130, 60), QPointF(80,80));
    painter->drawLine(QPointF(130, 140), QPointF(80,120));

    //strzalka
    painter->drawLine(QPointF(120,140), QPointF(123, 132.5));
    painter->drawLine(QPointF(120,140), QPointF(130, 140));
    painter->drawLine(QPointF(130, 140), QPointF(123, 132.5));

    pen.setWidth(10);
    painter->setPen(pen);
    painter->drawLine(QPointF(80, 130), QPointF(80, 70));

    this->setScale(0.75);
}

QRectF FlashingFtransistorItem::boundingRect() const
{
    const qreal adjust = 4.5;
    return QRectF(QPointF(35-adjust, 45 - adjust), QPointF(150 + adjust, 155 + adjust));
}

void FlashingFtransistorItem::timerEvent(QTimerEvent *event)
{
    unsigned short tempLineBlue = getLineBlue();
    unsigned short tempLineRed = getLineRed();
    unsigned short tempLineGreen = getLineGreen();

    this->setLineBlue(this->getInteriorBlue());
    this->setLineRed(this->getInteriorRed());
    this->setLineGreen(this->getInteriorGreen());

    this->setInteriorBlue(tempLineBlue);
    this->setInteriorRed(tempLineRed);
    this->setInteriorGreen(tempLineGreen);

    killTimer(event->timerId());
    startTimer(this->getTime() * 1000);
}
