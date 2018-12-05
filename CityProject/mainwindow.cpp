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
    if(twin != NULL) twin->close();
    twin = new testWindow();
    //Building * h = new Tower();
    Building * h = new House();
    h->setSurfacePosition(0,0,0);
    twin->setAttribute(Qt::WA_DeleteOnClose);
    twin->loadBuilding(h);
    twin->show();
}
