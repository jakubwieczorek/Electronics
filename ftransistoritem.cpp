#include "ftransistoritem.h"

FtransistorItem::FtransistorItem()
{
    setFlag(GraphicsItemFlag::ItemIsMovable);
    setFlag(GraphicsItemFlag::ItemIsSelectable);
    QElem::setBacklightRect(boundingRect());
}

void FtransistorItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    if(getBacklight())
        QElem::paint(painter, option, widget);

    this->paint(painter);
}

void FtransistorItem::paint(QPainter *painter)
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
    Ftransistor::setX(static_cast<unsigned short>(x()));
    Ftransistor::setY(static_cast<unsigned short>(y()));//real to double wiec <0 double na ushort
    // daje np. 66554

    qDebug()<<QString::number(Ftransistor::getX())<<QString::number(Ftransistor::getY());
    //qDebug()<<QString::number(x())<<QString::number(y());
}

QRectF FtransistorItem::boundingRect() const
{
    const qreal adjust = 4.5;
    return QRectF(QPointF(35-adjust, 45 - adjust), QPointF(150 + adjust, 155 + adjust));
}
