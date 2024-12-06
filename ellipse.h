#ifndef ELLIPSE_H
#define ELLIPSE_H

#include "shape.h"

class Ellipse : public shape
{
    Q_OBJECT
public:
    Ellipse(QPointF startPoint, QGraphicsObject *parent = nullptr);

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
};

#endif // ELLIPSE_H
