#ifndef MYSCENE_H
#define MYSCENE_H

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QKeyEvent>
#include <QList>
#include <QPointF>
#include <QHash>

#include <QFile>
#include <QTextStream>
#include <QImage>
#include <QPainter>
#include <QPixmap>

#include "shape.h"
#include "line.h"


class MyScene : public QGraphicsScene
{
    Q_OBJECT
public:
    MyScene(QObject *parent = nullptr);
    ~MyScene();

    int typeShape() const;
    void setTypeShape(const int type);

    enum ShapeTypes{
        RectangleType,
        EllipseType,
        TriangleType,
        LineType
    };

    void setMoveMode(bool mode);
    bool getMoveMode() const;

    void setDeleteMode(bool mode);

    void saveToFile(const QString &fileName);
    void loadFromFile(const QString &fileName);
private:
    shape *tempShape;
    int f_typeShape;
    bool paintingCancelling;

    bool paintingLineMode;
    shape *startShapeForLine;
    Line *tempLine;
    QList <Line*> lines;

    //for loading images
    QPixmap pixmap;

    //QList<QPixmap> pixmapLayers;
    // //added
    QList <shape*> shapes;
    QHash<shape*, QList<Line*>> shapeToLinesHash;

    void updateLinesForShape(shape *shape);
    // //added
    bool moveMode;
    QPointF dragStartPos;
    shape *draggedShape;

    bool deleteMode;

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;

    void drawForeground(QPainter *painter, const QRectF &rect) override;
public slots:
    void onShapePositionChanged(QPointF newPosition);
};

#endif // MYSCENE_H
