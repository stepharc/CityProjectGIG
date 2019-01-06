#ifndef GRIDSURFACEDIALOG_H
#define GRIDSURFACEDIALOG_H

#include <QDialog>
#include <QtGui>
#include <QtCore>
#include <QGraphicsScene>
#include <QGraphicsRectItem>

namespace Ui {
class GridSurfaceDialog;
}

class GridSurfaceDialog : public QDialog
{
    Q_OBJECT

public:
    explicit GridSurfaceDialog(int cityWidth, int cityDepth, int nbGridRow, int nbGridCol, QWidget *parent = nullptr);
    ~GridSurfaceDialog();

private:
    bool eventFilter(QObject *watched, QEvent *event);
    void modifyGridColors(int x, int y);
    Ui::GridSurfaceDialog *ui;
    QGraphicsScene *scene;
    std::vector<std::vector<QGraphicsRectItem *>> grid_;
    QBrush currBrush_;
    float rectSurfaceWidth_, rectSurfaceDepth_;
    int dimCubeSelection_;
    int cubeDim_;

private slots:
    void on_comboBox_currentIndexChanged(int index);
    void on_spinBox_valueChanged(int arg1);
    void on_buttonBox_accepted();

signals:
    void sendSurfaceData(std::vector<std::vector<QGraphicsRectItem *>>);
};

#endif // GRIDSURFACEDIALOG_H
