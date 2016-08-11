#include "ftransistoritem.h"

FtransistorItem::FtransistorItem()
{
    setFlag(GraphicsItemFlag::ItemIsMovable);
    setFlag(GraphicsItemFlag::ItemIsSelectable);
}

void FtransistorItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QRectF ellipse = boundingRect();

    QPen linePen(Qt::black, 3.5);
    painter->setPen(linePen);

    painter->drawEllipse(ellipse);
}

QRectF FtransistorItem::boundingRect() const
{
    return QRectF(QPointF(10,10), QPointF(100,100));
}
