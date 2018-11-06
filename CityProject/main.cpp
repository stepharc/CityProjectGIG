#include "mainwindow.h"

int main(int argc, char *argv[])
{
    srand(time(NULL));
    QApplication a(argc, argv);
    MainWindow mWin;
    mWin.show();
    return a.exec();
}
