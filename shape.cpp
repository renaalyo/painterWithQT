#include "shape.h"
#include "myscene.h"

shape::shape(QPointF point, QGraphicsObject *parent) :
    QGraphicsObject(parent), f_startPoint(point), f_endPoint(point)
{
    this->setStartPoint(mapFromScene(point));
    this->setEndPoint(mapFromScene(point));
}

QRectF shape::boundingRect() const{
    return QRectF(f_startPoint, f_endPoint).normalized();
}

void shape::updateRectangle(){
    this->update(QRectF(f_startPoint, f_endPoint).normalized());
}

void shape::setStartPoint(const QPointF &point){
    f_startPoint = point;
};

void shape::setEndPoint(const QPointF &point) {
    f_endPoint = point;
};

QPointF shape::startPoint() const{
    return f_startPoint;
};

QPointF shape::endPoint() const{
    return f_endPoint;
};

//added
void shape::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    MyScene *scene = dynamic_cast<MyScene*>(this->scene());
    if (scene && scene->getMoveMode() && event->button() == Qt::LeftButton) {
        setCursor(QCursor(Qt::ClosedHandCursor));
        dragStartPos = event->scenePos();
        isDragging = true;
    } else {
        QGraphicsObject::mousePressEvent(event);
    }
}


void shape::mouseMoveEvent(QGraphicsSceneMouseEvent *event) {
    MyScene *scene = dynamic_cast<MyScene*>(this->scene());
    if (scene && scene->getMoveMode() && isDragging && event->buttons() & Qt::LeftButton) {
        QPointF delta = event->scenePos() - dragStartPos;
        moveBy(delta.x(), delta.y());
        dragStartPos = event->scenePos();
        emit positionChanged(scenePos());
    } else {
        QGraphicsObject::mouseMoveEvent(event);
    }
}

void shape::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {
    MyScene *scene = dynamic_cast<MyScene*>(this->scene());
    if (scene && scene->getMoveMode() && isDragging && event->button() == Qt::LeftButton) {
        setCursor(QCursor(Qt::ArrowCursor));
        isDragging = false;
    } else {
        QGraphicsObject::mouseReleaseEvent(event);
    }
}
