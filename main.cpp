#include "testwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    testWindow tWin;
    House testHouse = House();
    Tower testTower = Tower();
    tWin.show();   //Exécution de la fenêtre de rendu OpenGL

    return a.exec();
}
