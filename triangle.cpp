#include "triangle.h"

Triangle::Triangle(QPointF point, QGraphicsObject *parent) : shape(point, parent) {}

void Triangle::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    painter->setPen(QPen(Qt::white, 2));
    QPolygonF polygon = trianglePolygon();
    painter->drawPolygon(polygon);

    Q_UNUSED(option)
    Q_UNUSED(widget)
}

QPolygonF Triangle::trianglePolygon() const {
    QPolygonF polygon;

    QPointF top = QPointF(boundingRect().center().x(), boundingRect().top());
    QPointF left = QPointF(boundingRect().left(), boundingRect().bottom());
    QPointF right = QPointF(boundingRect().right(), boundingRect().bottom());


    polygon << top << left << right;
    return polygon;
}

QPointF Triangle::centroid() const {
    QPolygonF polygon = trianglePolygon();
    QPointF top = polygon.at(0);
    QPointF left = polygon.at(1);
    QPointF right = polygon.at(2);

    return QPointF(
        (top.x() + left.x() + right.x()) / 3.0,
        (top.y() + left.y() + right.y()) / 3.0
    );
}
