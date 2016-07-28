#include "mysquare.h"

MySquare::MySquare()
{
    setFlag(QGraphicsItem::ItemIsMovable);
}

void MySquare::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QPolygon poly;

    poly<<QPoint(10,10);
    poly<<QPoint(100,10);
    poly<<QPoint(10,100);
    poly<<QPoint(100,100);

    QPen blackPen(Qt::black, 6);
    painter->setPen(blackPen);

    QPolygonF polyf(poly);
    painter->drawPolygon(polyf);
}

QRectF MySquare::boundingRect() const
{
    return QRectF(QPointF(0,0), QPointF(100,100));
}
