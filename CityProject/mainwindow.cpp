#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionBuildingWin_triggered()
{
    qDebug("loulilol");
    House h = House();
    h.setSurfacePosition(0,0,0);
    testWindow * bwin = new testWindow();
    bwin->setAttribute(Qt::WA_DeleteOnClose);
    bwin->loadBuilding(h);
    bwin->show();
}
