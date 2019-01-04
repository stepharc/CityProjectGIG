#include <QApplication>
#include <iostream>

#include "mainwindow.h"

int main(int argc, char *argv[])
{
    srand(time(nullptr));
    QApplication a(argc, argv);

    MainWindow mWin;
    mWin.show();

    return a.exec();
}
