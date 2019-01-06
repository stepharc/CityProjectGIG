#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QApplication>

#include "baseglwidget.h"
#include "district.h"
#include "gridsurfacedialog.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_actionBuildingWin_triggered();

    void on_comboBox_activated(int index);

public slots:
    void on_GridSurfaceDialog_sendSurfaceData(std::vector<std::vector<QGraphicsRectItem *>>);

private:
    Ui::MainWindow *ui;
    baseGLWidget * twin;
    GridSurfaceDialog * gswin;
    std::vector<std::vector<District *>> surfaceGrid_;
};

#endif // MAINWINDOW_H
