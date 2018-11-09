#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QApplication>
#include "house.h"
#include "tower.h"
#include "testwindow.h"

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

private:
    Ui::MainWindow *ui;
    testWindow * twin;
};

#endif // MAINWINDOW_H
