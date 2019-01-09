#include "gridsurfacedialog.h"
#include "ui_gridsurfacedialog.h"

#include <QGraphicsView>
#include <QScrollBar>
#include <iostream>

GridSurfaceDialog::GridSurfaceDialog(int nbGridCol, int nbGridRow, float rsww, float rsdd, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GridSurfaceDialog),
    dimCubeSelection_(0),
    cubeDim_(30)
{
    QString rsw = QString::number(double(rsww));
    QString rsd = QString::number(double(rsdd));

    ui->setupUi(this);

    scene = new QGraphicsScene(this);
    ui->graphicsView->setAlignment(Qt::AlignTop | Qt::AlignLeft);
    ui->graphicsView->setScene(scene);
    ui->gridInfo->setText("Info : One rectangle in grid = one area in city's surface area, dimensions : " + rsw + " * " + rsd);

    // Add event listener to the graphics view, so we can detect mouse click.
    ui->graphicsView->viewport()->installEventFilter(this);

    currBrush_ = QBrush(Qt::green);
    QPen blackPen(Qt::black);
    blackPen.setWidth(0);

    // Init surface grid with 100 % Periphery.
    for (int i = 0; i < nbGridRow; i++){
        std::vector<QGraphicsRectItem *> gridrow;
        for(int j = 0; j < nbGridCol ; j++){
            QGraphicsRectItem * rec = scene->addRect(i * cubeDim_, j * cubeDim_, cubeDim_, cubeDim_, blackPen);
            rec->setBrush(currBrush_);
            gridrow.push_back(rec);
        }
        grid_.push_back(gridrow);
    }
}

GridSurfaceDialog::~GridSurfaceDialog()
{
    delete ui;
}

// Event listener for the graphic view.
bool GridSurfaceDialog::eventFilter(QObject *watched, QEvent *event){
    if(event->type() == QEvent::MouseButtonPress){
        QMouseEvent* e = static_cast<QMouseEvent*>(event);
        if(e->buttons() == Qt::LeftButton){
            int addx = ui->graphicsView->horizontalScrollBar()->value();
            int addy = ui->graphicsView->verticalScrollBar()->value();
            modifyGridColors(e->x() + addx, e->y() + addy);
        }else{
            return QObject::eventFilter(watched, event);
        }
        return true;
    }else{
        return QObject::eventFilter(watched, event);
    }
}

void GridSurfaceDialog::modifyGridColors(int x, int y){
    // Get indexes of clicked square.
    int row = y / cubeDim_;
    int col = x / cubeDim_;

    // Compute indexes of grid area to color (Centered at clicked square,
    // sides length for each : 1 + (2 * dimCubeSelection) squares).
    int rowmin = row - dimCubeSelection_;
    rowmin = rowmin < 0 ? 0 : rowmin;
    int rowmax = row + dimCubeSelection_;
    rowmax = rowmax >= int(grid_.at(0).size()) ? int(grid_.at(0).size()) - 1 : rowmax;
    int colmin = col - dimCubeSelection_;
    colmin = colmin < 0 ? 0 : colmin;
    int colmax = col + dimCubeSelection_;
    colmax = colmax >= int(grid_.size()) ? int(grid_.size()) - 1 : colmax;

    // Change grid area selected to current color, if needed.
    for(int c = colmin; c <= colmax; c++){
        for(int r = rowmin; r <= rowmax; r++){
            QBrush b = grid_.at(ulong(c)).at(ulong(r))->brush();
            if(b != currBrush_) grid_.at(ulong(c)).at(ulong(r))->setBrush(currBrush_);
        }
    }
}

// Change color based on district type we want to represent.
void GridSurfaceDialog::on_comboBox_currentIndexChanged(int index)
{
    switch(index){
        case 0: // Periphery
            currBrush_ = QBrush(Qt::green);
            break;
        case 1: // Downtown
            currBrush_ = QBrush(Qt::red);
            break;
        case 2: // Activity Area
            currBrush_ = QBrush(Qt::gray);
            break;
    }
}

// Change square selection's side length.
void GridSurfaceDialog::on_spinBox_valueChanged(int arg1)
{
    dimCubeSelection_ = arg1;
}

// Send surface grid to MainWindow.
void GridSurfaceDialog::on_buttonBox_accepted()
{
    emit sendSurfaceData(grid_);
}
