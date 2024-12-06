#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPainter>
#include <QResizeEvent>
#include <QFileDialog>
#include "MyScene.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    MyScene *scene;
    QGraphicsView *view;

private slots:
    void on_pushButtonRectangle_clicked();
    void on_pushButtonEllipse_clicked();
    void on_pushButtonTriangle_clicked();
    void on_pushButtonLine_clicked();

    void on_pushButtonMove_clicked();
    void on_pushButtonDelete_clicked();

    void on_pushButtonLoad_clicked();
    void on_pushButtonSave_clicked();
};
#endif // MAINWINDOW_H
