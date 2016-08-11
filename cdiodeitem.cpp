#include "cdiodeitem.h"

CdiodeItem::CdiodeItem()
{
    setFlag(QGraphicsItem::ItemIsMovable);
    setFlag(QGraphicsItem::ItemIsSelectable);
}

void CdiodeItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
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

    QColor brushColor(this->getInteriorRed(), this->getInteriorBlue(), getInteriorGreen());
    QBrush fillBrush;
    fillBrush.setColor(brushColor);
    fillBrush.setStyle(Qt::SolidPattern);

    QPainterPath path;
    path.addPolygon(poly);

    QColor penColor(this->getLineRed(), this->getLineBlue(), getLineGreen());
    QPen pen(penColor, 5);
    pen.setJoinStyle(Qt::MiterJoin);
    painter->setPen(pen);

    for(int i=0; i<4; i++)
    {
        painter->drawLine(line[i]);
    }

    painter->drawPolygon(poly);
    painter->fillPath(path, fillBrush);

    //update(); - powoduje ze caly czas na nowo sie maluje obiekt
}

QRectF CdiodeItem::boundingRect() const
{
    const qreal adjust = 4.5;
    return QRectF(QPointF(-100 - adjust, 0 - adjust), QPointF(50 + adjust, 100 + adjust));
}