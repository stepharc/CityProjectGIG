#include <QApplication>

#include "baseglwidget.h"

//#include "mainwindow.h"

int main(int argc, char *argv[])
{
    srand(time(nullptr));
    QApplication a(argc, argv);
    /*MainWindow mWin;
    mWin.show();*/

    baseGLWidget w;
    w.show();

    return a.exec();
}
