#include "qelem.h"

QElem::QElem()
{
    backlight = false;
}

void QElem::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    QPen backlightPen(Qt::black, 5);
    backlightPen.setJoinStyle(Qt::MiterJoin);
    painter->setPen(backlightPen);
    painter->drawRect(backlightRect);
    QColor backlightColor(183,224,255);
    QBrush backlightRectBrush(backlightColor);
    painter->fillRect(backlightRect, backlightRectBrush);
}
