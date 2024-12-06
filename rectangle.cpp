#include "rectangle.h"

Rectangle::Rectangle(QPointF point, QGraphicsObject *parent) : shape(point, parent){};

Rectangle::~Rectangle(){};

void Rectangle::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
    painter->setPen(QPen(Qt::white, 2));

    QRectF rect(startPoint(), endPoint());
    painter->drawRect(rect.normalized());

    Q_UNUSED(option)
    Q_UNUSED(widget)
};
