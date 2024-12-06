#include "MyScene.h"
#include "shape.h"
#include "rectangle.h"
#include "triangle.h"
#include "ellipse.h"
#include "line.h"

MyScene::MyScene(QObject *parent) :
    QGraphicsScene(parent), f_typeShape(RectangleType),
    tempShape(nullptr), paintingCancelling(false),
    paintingLineMode(false), startShapeForLine(nullptr),
    tempLine(nullptr), moveMode(false), draggedShape(nullptr){

};


MyScene::~MyScene(){
    qDeleteAll(lines);

};

int MyScene::typeShape() const{
    return f_typeShape;
}

void MyScene::setMoveMode(bool mode) {
    moveMode = mode;
}

bool MyScene::getMoveMode() const {
    return moveMode;
}

void MyScene::setDeleteMode(bool mode) {
    deleteMode = mode;
}

void MyScene::onShapePositionChanged(QPointF newPosition) {
    shape *changedShape = qobject_cast<shape*>(sender());
    if (changedShape) {
        updateLinesForShape(changedShape);
    }
}

void MyScene::setTypeShape(const int type){
    f_typeShape = type;
    paintingLineMode = (type == LineType);

    if (!paintingLineMode) {
        startShapeForLine = nullptr;
        if (tempLine) {
            delete tempLine;
            tempLine = nullptr;
        }
    }
}

void MyScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event){
    if (moveMode && draggedShape && event->buttons() & Qt::LeftButton){
        QPointF delta = event->scenePos() - dragStartPos;
        draggedShape->moveBy(delta.x(), delta.y());
        dragStartPos = event->scenePos();

        emit draggedShape->positionChanged(dragStartPos);
        updateLinesForShape(draggedShape);
    }
    else if (tempShape && !paintingCancelling){
        tempShape->setEndPoint(event->scenePos());
    }
    else if (paintingLineMode && startShapeForLine) {
        if (tempLine) {
            delete tempLine;
        }
        tempLine = new Line(startShapeForLine, dynamic_cast<shape*>(itemAt(event->scenePos(), QTransform())));
    }
    this->update(QRectF(0,0,this->width(), this->height()));

};

void MyScene::mousePressEvent(QGraphicsSceneMouseEvent *event){
    if (event->button() == Qt::LeftButton){

        if (moveMode) {
            draggedShape = dynamic_cast<shape*>(itemAt(event->scenePos(), QTransform()));
            if (draggedShape) {
                dragStartPos = event->scenePos();
                draggedShape->setCursor(QCursor(Qt::ClosedHandCursor));
                connect(draggedShape, &shape::positionChanged, this, &MyScene::onShapePositionChanged);
            }
        }else if (deleteMode){
            shape *shapeToDelete = dynamic_cast<shape*>(itemAt(event->scenePos(), QTransform()));
            if (shapeToDelete) {

                QList<Line*> linesToDelete = shapeToLinesHash.value(shapeToDelete);

                for (Line *line : linesToDelete) {

                    shape *otherShape = (line->getStartLine() == shapeToDelete) ? line->getEndLine() : line->getStartLine();
                    if (otherShape) {
                        shapeToLinesHash[otherShape].removeOne(line);
                    }

                    lines.removeOne(line);
                    delete line;
                }

                shapeToLinesHash.remove(shapeToDelete);
                shapes.removeOne(shapeToDelete);
                delete shapeToDelete;
            }
        }
        else{
            paintingCancelling = false;

            if (paintingLineMode){
                if (!startShapeForLine){
                    startShapeForLine = dynamic_cast<shape*>(itemAt(event->scenePos(), QTransform()));

                }else{
                    shape *endShape = dynamic_cast<shape*>(itemAt(event->scenePos(), QTransform()));
                    if (endShape && endShape != startShapeForLine) {
                        Line *newLine = new Line(startShapeForLine, endShape);
                        lines.append(newLine);

                        shapeToLinesHash[startShapeForLine].append(newLine);
                        shapeToLinesHash[endShape].append(newLine);

                        startShapeForLine = nullptr;
                        delete tempLine;
                        tempLine = nullptr;
                    }
                }

                }else{
                    switch (f_typeShape){
                    case RectangleType:{
                        tempShape = new Rectangle(event->scenePos());
                        break;
                    }
                    case EllipseType:{
                        tempShape = new Ellipse(event->scenePos());
                        break;
                    }
                    case TriangleType:{
                        tempShape = new Triangle(event->scenePos());
                        break;
                    }
                    }
                    this->addItem(tempShape);
                }
            }
        }else if (event->button() == Qt::RightButton){
            paintingCancelling = true;
            if (paintingLineMode && tempLine) {
                delete tempLine;
                tempLine = nullptr;
                startShapeForLine = nullptr;
            }
        }

    this->update(QRectF(0, 0, this->width(), this->height()));
};

void MyScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event){
    // if (event->button() == Qt::LeftButton && !paintingCancelling) {
    //     tempShape = nullptr;
    // } else if (paintingCancelling) {
    //     if (tempShape) {
    //         this->removeItem(tempShape);
    //         delete tempShape;
    //         tempShape = nullptr;
    //     }
    //     paintingCancelling = false;
    // }

    if (event->button() == Qt::LeftButton) {
        if (moveMode && draggedShape) {
            draggedShape->setCursor(QCursor(Qt::ArrowCursor));
            connect(draggedShape, &shape::positionChanged, this, &MyScene::onShapePositionChanged);

            draggedShape = nullptr;
        } else if (!paintingCancelling) {
            tempShape = nullptr;
        } else if (paintingCancelling) {
            if (tempShape) {
                this->removeItem(tempShape);
                delete tempShape;
                tempShape = nullptr;
            }
            paintingCancelling = false;
        }
    }
    QGraphicsScene::mouseReleaseEvent(event);
}

void MyScene::keyPressEvent(QKeyEvent *event) {
    if (event->key() == Qt::Key_Escape) {
        if (moveMode && draggedShape) {
            QPointF delta = dragStartPos - draggedShape->scenePos();
            draggedShape->moveBy(delta.x(), delta.y());
            draggedShape->setCursor(QCursor(Qt::ArrowCursor));
            draggedShape = nullptr;
            disconnect(draggedShape, &shape::positionChanged, this, &MyScene::onShapePositionChanged);

        } else {
            paintingCancelling = true;
            if (tempShape) {
                this->removeItem(tempShape);
                delete tempShape;
                tempShape = nullptr;
            }
            if (paintingLineMode && tempLine) {
                delete tempLine;
                tempLine = nullptr;
                startShapeForLine = nullptr;
            }
            this->update(QRectF(0, 0, this->width(), this->height()));
        }
    } else {
        QGraphicsScene::keyPressEvent(event);
    }
}

void MyScene::drawForeground(QPainter *painter, const QRectF &rect)
{
    QGraphicsScene::drawForeground(painter, rect);
    if (tempLine) {
        tempLine->paint(painter);
    }
    for (Line *line : lines) {
        line->paint(painter);
    }

    // for (const QPixmap &pixmap : pixmapLayers) {
    //     painter->drawPixmap(0, 0, pixmap);
    // }

    if (!pixmap.isNull()) {
        painter->drawPixmap(0, 0, pixmap);
    }

}

void MyScene::updateLinesForShape(shape *shape) {
    QList<Line*> lines = shapeToLinesHash.value(shape);
    for (Line *line : lines) {
        line->updatePosition();

        //this->update(line->boundingRect());
    }
}

void MyScene::saveToFile(const QString &fileName)
{
    QImage image(sceneRect().size().toSize(), QImage::Format_ARGB32);
    image.fill(Qt::transparent);

    QPainter painter(&image);
    render(&painter);
    painter.end();

    image.save(fileName);
}

void MyScene::loadFromFile(const QString &fileName)
{
    // QPixmap pixmap(fileName);
    // if (pixmap.isNull())
    //     return;

    // pixmapLayers.append(pixmap);
    QPixmap newPixmap(fileName);
    if (newPixmap.isNull())
        return;

    pixmap = newPixmap;
    this->update(QRectF(0, 0, pixmap.width(), pixmap.height()));
}
