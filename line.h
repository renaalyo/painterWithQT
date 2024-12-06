#ifndef LINE_H
#define LINE_H

#include <QObject>
#include <QPointF>
#include <QPainter>
#include "shape.h"


class Line : public QObject
{
    Q_OBJECT
public:
    Line(shape *startLine, shape *endLine, QObject *parent = nullptr);
    Line(const QPointF &startPoint, const QPointF &endPoint, QObject *parent = nullptr);

    void paint(QPainter *painter);
    QRectF boundingRect() const;

    void setStartLine(shape *startLine);
    void setEndLine(shape *endLine);

    //added
    // shape* startShape() const;
    // shape* endShape() const;
    shape* getStartLine() const;
    shape* getEndLine() const;
    void updatePosition();
private:
    shape *m_startLine;
    shape *m_endLine;

};

#endif // LINE_H
