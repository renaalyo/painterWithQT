#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    scene = new MyScene();
    view = ui->graphicsView;
    view->setScene(scene);
    view->setRenderHint(QPainter::Antialiasing);                // Устанавливаем сглаживание
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);   // Отключаем скроллбар по вертикали
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff); // Отключаем скроллбар по горизонтали

    view->setFixedSize(1800, 600);
    scene->setSceneRect(0, 0, 1800, 600);

}

MainWindow::~MainWindow()
{
    delete scene;
    delete ui;
}

void MainWindow::on_pushButtonRectangle_clicked()
{
    scene->setTypeShape(MyScene::RectangleType);
    scene->setMoveMode(false);
    scene->setDeleteMode(false);
}


void MainWindow::on_pushButtonEllipse_clicked()
{
    scene->setTypeShape(MyScene::EllipseType);
    scene->setMoveMode(false);
    scene->setDeleteMode(false);
}


void MainWindow::on_pushButtonTriangle_clicked()
{
    scene->setTypeShape(MyScene::TriangleType);
    scene->setMoveMode(false);
    scene->setDeleteMode(false);
}


void MainWindow::on_pushButtonLine_clicked()
{
    scene->setTypeShape(MyScene::LineType);
    scene->setMoveMode(false);
    scene->setDeleteMode(false);
}


void MainWindow::on_pushButtonMove_clicked()
{
    // QPointF mousePos = view->mapToScene(view->mapFromGlobal(QCursor::pos()));
    // scene->setMoveMode(true); // Включаем режим перемещения
    // emit scene->moveShapeToPos(mousePos);
    scene->setMoveMode(true);
    scene->setDeleteMode(false);
}


void MainWindow::on_pushButtonDelete_clicked()
{
    //scene->;
    scene->setDeleteMode(true);
    scene->setMoveMode(false);
}


void MainWindow::on_pushButtonLoad_clicked()
{
    scene->setDeleteMode(false);
    scene->setMoveMode(false);
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), "", tr("PNG Files (*.png);;All Files (*)"));
    if (!fileName.isEmpty()) {
        scene->loadFromFile(fileName);
    }
}


void MainWindow::on_pushButtonSave_clicked()
{
    scene->setDeleteMode(false);
    scene->setMoveMode(false);
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"), "", tr("PNG Files (*.png);;All Files (*)"));
    if (!fileName.isEmpty()) {
        scene->saveToFile(fileName);
    }
}

