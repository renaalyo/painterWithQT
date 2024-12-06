#ifndef RECTANGLE_H
#define RECTANGLE_H

#include <QGraphicsObject>
#include <QPainter>
#include "shape.h"

class Rectangle : public shape
{
    Q_OBJECT

public:
    Rectangle(QPointF point, QGraphicsObject *parent = nullptr);
    ~Rectangle();

private:
    //void paint(QPainter *painter) override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;

};

#endif // RECTANGLE_H
