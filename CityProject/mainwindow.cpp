#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "house.h"
#include "tower.h"

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
    if(twin != nullptr) twin->close();
    std::vector<baseGeometry *> geos_;

    QString vsp = "../shaders/basevertex.vert";
    QString fsp = "../shaders/basefrag.frag";
    QString fsp2 = "../shaders/testfragment.frag";
    baseGeometry * g1 = new baseGeometry(vsp, fsp, QVector3D(1, 1, -4), QVector3D(1, 1, 2));
    baseGeometry * g2 = new baseGeometry(vsp, fsp2, QVector3D(1, 1, -10), QVector3D(1, 5, 2));
    baseGeometry * g3 = new House(QVector3D(-1, 1, -4));
    baseGeometry * g4 = new Tower(QVector3D(1, 1, -10));

    geos_.push_back(g1);
    geos_.push_back(g2);
    geos_.push_back(g3);
    geos_.push_back(g4);

    twin = new baseGLWidget(geos_);
    twin->show();
}
