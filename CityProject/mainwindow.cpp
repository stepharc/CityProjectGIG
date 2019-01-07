#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "house.h"
#include "tower.h"
#include "periphery.h"
#include "downtown.h"
#include "activityarea.h"

#include <iostream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    twin = nullptr;
    gswin = nullptr;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionBuildingWin_triggered()
{
    if(twin != nullptr) twin->close();
    std::vector<baseGeometry *> geos_;

    /*QString vsp = "../shaders/basevertex.vert";
    QString fsp = "../shaders/basefrag.frag";
    QString fsp2 = "../shaders/testfragment.frag";
    baseGeometry * g1 = new baseGeometry(vsp, fsp, QVector3D(1, 1, -4), QVector3D(1, 1, 2));
    baseGeometry * g2 = new baseGeometry(vsp, fsp2, QVector3D(1, 1, -10), QVector3D(1, 5, 2));*/

    Building * b1 = new House(QVector3D(0, 0, -4));
    baseGeometry * g3 = b1->getShapeGeometry();
    Building * b2 = new Tower(QVector3D(0, 0, -15));
    baseGeometry * g4 = b2->getShapeGeometry();
    Building * b3 = new Tower(QVector3D(-20, 0, -10));
    baseGeometry * g5 = b3->getShapeGeometry();

    /*geos_.push_back(g1);
    geos_.push_back(g2);*/
    geos_.push_back(g3);
    geos_.push_back(g4);
    geos_.push_back(g5);

    twin = new baseGLWidget(geos_);
    twin->show();
}

void MainWindow::on_comboBox_activated(int index)
{
    switch(index){
        case 0: // "Concentrique" option
            std::cout << "Concentrique : not implemented yet." << std::endl;
            break;
        case 1: // "100 % Centre-ville" option
            std::cout << "100 % Centre-ville : not implemented yet." << std::endl;
            break;
        case 2: // "100 % Périphérie" option
            std::cout << "100 % Périphérie : not implemented yet." << std::endl;
            break;
        case 3: // "100 % ZA" option
            std::cout << "100 % ZA : not implemented yet." << std::endl;
            break;
        case 4: // "Personnalisée..." option
            if(gswin != nullptr) gswin->close();
            gswin = new GridSurfaceDialog(1000, 1000, 75, 75);
            connect(gswin, &GridSurfaceDialog::sendSurfaceData,
                    this, &MainWindow::on_GridSurfaceDialog_sendSurfaceData);
            gswin->show();
            break;
    }
}

void MainWindow::on_GridSurfaceDialog_sendSurfaceData(std::vector<std::vector<QGraphicsRectItem *>> grid){
    //Don't forget to erase old surfaceGrid_ if there's an existing one.
    surfaceGrid_.erase(surfaceGrid_.begin(), surfaceGrid_.end());

    for(ulong i = 0; i < grid.size(); i++){
        std::vector<District *> col;
        for(ulong j = 0; j < grid.at(i).size(); j++){
            QGraphicsRectItem * rec = grid.at(i).at(j);
            QBrush rb = rec->brush();
            if(rb.color() == Qt::green){
                col.push_back(new Periphery());
            }else{
                if(rb.color() == Qt::red){
                    col.push_back(new Downtown());
                }else{
                    col.push_back(new ActivityArea());
                }
            }
        }
        surfaceGrid_.push_back(col);
    }

    std::cout << "Surface grid loaded successfully." << std::endl;
}
