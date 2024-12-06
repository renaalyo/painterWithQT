#ifndef SHAPE_H
#define SHAPE_H

#include <QGraphicsSceneMouseEvent>
#include <QGraphicsObject>
#include <QPainter>
#include <QCursor>



class shape : public QGraphicsObject
{
    Q_OBJECT

public:
    shape(QPointF point, QGraphicsObject *parent = nullptr);

    QPointF center() const { return boundingRect().center(); }

    void setStartPoint(const QPointF &point);
    void setEndPoint(const QPointF &point);

    QPointF startPoint() const;
    QPointF endPoint() const;

    QRectF boundingRect() const override;

    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0) override = 0;

    virtual ~shape() = default;

protected:
    QPointF f_startPoint;
    QPointF f_endPoint;

    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;

    //added
    QPointF dragStartPos;
    bool isDragging;

signals:
    void positionChanged(QPointF newPosition);

public slots:
    void updateRectangle();
};

#endif // SHAPE_H
