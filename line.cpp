#include "line.h"
#include "triangle.h"

Line::Line(shape *startLine, shape *endLine, QObject *parent)
    : QObject(parent), m_startLine(startLine), m_endLine(endLine){}

void Line::setStartLine(shape *startLine) {
    m_startLine = startLine;
}

void Line::setEndLine(shape *endLine)
{
    m_endLine = endLine;
}

shape* Line::getStartLine() const {
    return m_startLine;
}

shape* Line::getEndLine() const {
    return m_endLine;
}

void Line::paint(QPainter *painter)
{
    if (m_startLine && m_endLine) {
        painter->setPen(QPen(Qt::white, 2));

        QPointF startCenter = m_startLine->boundingRect().center();
        QPointF endCenter = m_endLine->boundingRect().center();

        if (Triangle *startTriangle = dynamic_cast<Triangle*>(m_startLine)) {
            startCenter = startTriangle->centroid();
        }
        if (Triangle *endTriangle = dynamic_cast<Triangle*>(m_endLine)) {
            endCenter = endTriangle->centroid();
        }
        painter->drawLine(startCenter, endCenter);
    }
}

QRectF Line::boundingRect() const
{
    if (m_startLine && m_endLine) {
        QPointF startCenter = m_startLine->boundingRect().center();
        QPointF endCenter = m_endLine->boundingRect().center();
        if (Triangle *startTriangle = dynamic_cast<Triangle*>(m_startLine)) {
            startCenter = startTriangle->centroid();
        }
        if (Triangle *endTriangle = dynamic_cast<Triangle*>(m_endLine)) {
            endCenter = endTriangle->centroid();
        }
        return QRectF(startCenter, endCenter).normalized();
    }
    return QRectF();
}

void Line::updatePosition() {

    if (m_startLine && m_endLine) {

        QPointF startCenter = m_startLine->center();
        QPointF endCenter = m_endLine->center();

        if (Triangle *startTriangle = dynamic_cast<Triangle*>(m_startLine)) {
            startCenter = startTriangle->centroid();
        }
        if (Triangle *endTriangle = dynamic_cast<Triangle*>(m_endLine)) {
            endCenter = endTriangle->centroid();
        }

    }
}




