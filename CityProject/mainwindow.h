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
    void on_MainWindow_surfaceLoaded();
    void on_MainWindow_surfaceNotLoaded();
    void on_cityWidth_valueChanged(int arg1);
    void on_nbDistrictsCols_valueChanged(int arg1);
    void on_nbDistrictsRows_valueChanged(int arg1);
    void on_cityDepth_valueChanged(int arg1);

signals :
    void surfaceLoaded();
    void surfaceNotLoaded();

public slots:
    void on_GridSurfaceDialog_sendSurfaceData(std::vector<std::vector<QGraphicsRectItem *>>);

private:
    void fillSurfaceGrid(int nbRow, int nbCol, int choice);
    void fillConcentricSurfaceGrid(int nbRow, int nbCol);

    Ui::MainWindow *ui;
    baseGLWidget * twin;
    GridSurfaceDialog * gswin;
    std::vector<std::vector<District *>> surfaceGrid_;
    int cityWidth_, cityDepth_, nbDistrictsCols_, nbDistrictsRows_;
    float rsw_, rsd_;
};

#endif // MAINWINDOW_H
