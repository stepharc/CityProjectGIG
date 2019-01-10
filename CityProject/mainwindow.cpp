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
    cityWindow = nullptr;
    cityWidth_ = ui->cityWidth->value();
    cityDepth_ = ui->cityDepth->value();
    nbDistrictsCols_ = ui->nbDistrictsCols->value();
    nbDistrictsRows_ = ui->nbDistrictsRows->value();
    rsw_ = cityWidth_ / nbDistrictsCols_;
    rsd_ = cityDepth_ / nbDistrictsRows_;
    connect(this, &MainWindow::surfaceLoaded,
            this, &MainWindow::on_MainWindow_surfaceLoaded);
    connect(this, &MainWindow::surfaceNotLoaded,
            this, &MainWindow::on_MainWindow_surfaceNotLoaded);
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

void MainWindow::fillSurfaceGrid(int nbRow, int nbCol, int choice){
    for(int i = 0; i < nbCol; i++){
        std::vector<District *> col;
        for(int j = 0; j < nbRow; j++){
            if(choice == 1){
                col.push_back(new Downtown(i, j, rsw_, rsd_));
            }else{
                if(choice == 2){
                    col.push_back(new Periphery(i, j, rsw_, rsd_));
                }else{
                    if(choice == 3){
                        col.push_back(new ActivityArea(i, j, rsw_, rsd_));
                    }else{
                        std::cout << "Invalid value, can't fill surface grid." << std::endl;
                        return;
                    }
                }
            }
        }
        surfaceGrid_.push_back(col);
    }
    emit surfaceLoaded();
}

// Fill the surface grid with a concentric pattern, so it will look like this :
// (A : ActivityArea, P : Periphery, D : Downtown)
//  A A A A A
//  A P P P A
//  A P D P A
//  A P P P A
//  A A A A A
void MainWindow::fillConcentricSurfaceGrid(int nbRow, int nbCol){
    // Compute column and row layer for this pattern (5 layers per column and 5 layers per row)
    int areaSizeCol = nbCol / 5;
    int areaSizeRow = nbRow / 5;

    for(int i = 0; i < nbCol; i++){
        std::vector<District *> col;
        for(int j = 0; j < nbRow; j++){
            bool found = false;
            if((j < areaSizeRow) || (j >= (4 * areaSizeRow))){
                 col.push_back(new ActivityArea(i, j, rsw_, rsd_));
                 found = true;
            }
            if((i < areaSizeCol) || (i >= (4 * areaSizeCol))){
                if(!found){
                    col.push_back(new ActivityArea(i, j, rsw_, rsd_));
                    found = true;
                }
            }
            if((j >= areaSizeRow && j < (2 * areaSizeRow)) || (j < (4 * areaSizeRow) && j >= (3 * areaSizeRow))){
                if(!found){
                    col.push_back(new Periphery(i, j, rsw_, rsd_));
                    found = true;
                }
            }
            if((i >= areaSizeCol && i < (2 * areaSizeCol)) || (i < (4 * areaSizeCol) && i >= (3 * areaSizeCol))){
                if(!found){
                    col.push_back(new Periphery(i, j, rsw_, rsd_));
                    found = true;
                }
            }
            if(!found){
                col.push_back(new Downtown(i, j, rsw_, rsd_));
            }
        }
        surfaceGrid_.push_back(col);
    }
    emit surfaceLoaded();
}

void MainWindow::on_comboBox_activated(int index)
{
    switch(index){
        case 0: // "Concentrique" option
            if(gswin != nullptr) gswin->close();
            emit surfaceNotLoaded();
            fillConcentricSurfaceGrid(nbDistrictsRows_, nbDistrictsCols_);
            break;
        case 1: // "100 % Centre-ville" option
            if(gswin != nullptr) gswin->close();
            emit surfaceNotLoaded();
            fillSurfaceGrid(nbDistrictsRows_, nbDistrictsCols_, index);
            break;
        case 2: // "100 % Périphérie" option
            if(gswin != nullptr) gswin->close();
            emit surfaceNotLoaded();
            fillSurfaceGrid(nbDistrictsRows_, nbDistrictsCols_, index);
            break;
        case 3: // "100 % ZA" option
            if(gswin != nullptr) gswin->close();
            emit surfaceNotLoaded();
            fillSurfaceGrid(nbDistrictsRows_, nbDistrictsCols_, index);
            break;
        case 4: // "Personnalisée..." option
            if(gswin != nullptr) gswin->close();
            emit surfaceNotLoaded();
            gswin = new GridSurfaceDialog(nbDistrictsRows_, nbDistrictsCols_, rsw_, rsd_);
            connect(gswin, &GridSurfaceDialog::sendSurfaceData,
                    this, &MainWindow::on_GridSurfaceDialog_sendSurfaceData);
            gswin->show();
            break;
    }
}

void MainWindow::on_GridSurfaceDialog_sendSurfaceData(std::vector<std::vector<QGraphicsRectItem *>> grid){
    for(ulong i = 0; i < grid.size(); i++){
        std::vector<District *> col;
        for(ulong j = 0; j < grid.at(i).size(); j++){
            QGraphicsRectItem * rec = grid.at(i).at(j);
            QBrush rb = rec->brush();
            if(rb.color() == Qt::green){
                col.push_back(new Periphery(int(i), int(j), rsw_, rsd_));
            }else{
                if(rb.color() == Qt::red){
                    col.push_back(new Downtown(int(i), int(j), rsw_, rsd_));
                }else{
                    col.push_back(new ActivityArea(int(i), int(j), rsw_, rsd_));
                }
            }
        }
        surfaceGrid_.push_back(col);
    }
    emit surfaceLoaded();
}

void MainWindow::on_MainWindow_surfaceLoaded(){
    std::cout << "Surface grid loaded successfully." << std::endl;
    ui->cityButton->setEnabled(true);
}

void MainWindow::on_MainWindow_surfaceNotLoaded(){
    //Don't forget to erase old surfaceGrid_ if there's an existing one.
    for(ulong i = 0; i < surfaceGrid_.size(); i++){
        for(ulong j = 0; j < surfaceGrid_.size(); j++){
            surfaceGrid_.at(i).erase(surfaceGrid_.at(i).begin() + int(j));
        }
    }
    surfaceGrid_.erase(surfaceGrid_.begin(), surfaceGrid_.end());

    ui->cityButton->setEnabled(false);
}

void MainWindow::on_cityWidth_valueChanged(int arg1)
{
    emit surfaceNotLoaded();
    cityWidth_ = arg1;
    rsw_ = cityWidth_ / nbDistrictsCols_;
}

void MainWindow::on_cityDepth_valueChanged(int arg1)
{
    emit surfaceNotLoaded();
    cityDepth_ = arg1;
    rsd_ = cityDepth_ / nbDistrictsRows_;
}

void MainWindow::on_nbDistrictsCols_valueChanged(int arg1)
{
    emit surfaceNotLoaded();
    if(arg1 != 0){
        nbDistrictsCols_ = arg1;
        rsw_ = cityWidth_ / nbDistrictsCols_;
    }
}

void MainWindow::on_nbDistrictsRows_valueChanged(int arg1)
{
    emit surfaceNotLoaded();
    if(arg1 != 0){
        nbDistrictsRows_ = arg1;
        rsd_ = cityDepth_ / nbDistrictsRows_;
    }
}

void MainWindow::on_cityButton_clicked()
{
    if(cityWindow != nullptr) cityWindow->close();
    std::vector<baseGeometry *> geos;

    QString vspSurface = "../shaders/basevertex.vert";
    QString fspSurface = "../shaders/surface.frag";
    //Set surface geometry, so city surface's top left corner will be at (0, 0, 0).
    //We take this scale, because base cube is 1 * 1;
    baseGeometry * surfaceGeometry = new baseGeometry(vspSurface, fspSurface, QVector3D(cityWidth_/2, 0, cityDepth_/2), QVector3D(cityWidth_/2, 0.1f, cityDepth_/2));
    geos.push_back(surfaceGeometry);

    /*baseGeometry * cubeTest = new baseGeometry(vspSurface, "../shaders/testfragment.frag", QVector3D(0, 5, 0), QVector3D(1, 5, 1));
    geos.push_back(cubeTest);*/

    for(int i = 0; i < nbDistrictsCols_; i++){
        for(int j = 0; j < nbDistrictsRows_; j++){
            District * b = surfaceGrid_.at(ulong(i)).at(ulong(j));
            baseGeometry * bg = b->getBuilding();
            geos.push_back(bg);
        }
    }

    cityWindow = new baseGLWidget(geos);
    cityWindow->show();
}
