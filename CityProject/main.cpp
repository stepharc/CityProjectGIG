#include "testwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    testWindow tWin;
    tWin.show();   //Exécution de la fenêtre de rendu OpenGL

    return a.exec();
}
