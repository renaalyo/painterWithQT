#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "shape.h"

class Triangle : public shape
{
    Q_OBJECT
public:
    Triangle(QPointF startPoint, QGraphicsObject *parent = nullptr);

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
    QPointF centroid() const;

private:
    QPolygonF trianglePolygon() const;

};

#endif // TRIANGLE_H
