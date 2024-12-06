#include "ellipse.h"

Ellipse::Ellipse(QPointF startPoint, QGraphicsObject *parent) : shape(startPoint, parent) {}

void Ellipse::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    painter->setPen(QPen(Qt::white, 2));

    QRectF rect(f_startPoint, f_endPoint);
    painter->drawEllipse(rect.normalized());

    Q_UNUSED(option);
    Q_UNUSED(widget);
}
