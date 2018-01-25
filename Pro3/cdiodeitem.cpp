#include "cdiodeitem.h"

CdiodeItem::CdiodeItem()
{
    setFlag(QGraphicsItem::ItemIsMovable);
    setFlag(QGraphicsItem::ItemIsSelectable);
    QElem::setBacklightRect(boundingRect());
}

void CdiodeItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    if(getBacklight())
        QElem::paint(painter, option, widget);

    this->paint(painter);
}

void CdiodeItem::paint(QPainter *painter)
{
    QLineF line[4];
    line[0].setPoints(QPoint(0,0), QPoint(0,100));
    line[1].setPoints(QPoint(0,50), QPoint(50,50));
    line[2].setPoints(QPoint(25,0), QPoint(25,100));
    line[3].setPoints(QPoint(-100,50), QPoint(-50,50));

    QPolygonF poly;
    poly<<QPointF(-50,0);
    poly<<QPointF(0,50);
    poly<<QPointF(-50,100);

    QColor brushColor(getInteriorRed(), getInteriorGreen(), getInteriorBlue());
    QBrush fillBrush;
    fillBrush.setColor(brushColor);
    fillBrush.setStyle(Qt::SolidPattern);

    QPainterPath path;
    path.addPolygon(poly);

    QColor penColor(getLineRed(), getLineGreen(), getLineBlue());
    QPen pen(penColor, 3.5);
    pen.setJoinStyle(Qt::MiterJoin);
    painter->setPen(pen);

    for(int i=0; i<4; i++)
    {
        painter->drawLine(line[i]);
    }

    painter->drawPolygon(poly);
    painter->fillPath(path, fillBrush);

    this->setScale(0.75);
}

QRectF CdiodeItem::boundingRect() const
{
    const qreal adjust = 4.5;
    return QRectF(QPointF(-100 - adjust, 0 - adjust), QPointF(50 + adjust, 100 + adjust));
}
