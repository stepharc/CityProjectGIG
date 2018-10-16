#ifndef BUILDING_H
#define BUILDING_H

#include <stdlib.h>
#include <QDebug>

// Classe mère de tous les types de bâtiments.

class Building
{
private :
    int height; // hauteur du bâtiment (m)
    int width;  // largeur du bâtiment (m)
public :
    // On laisse aux classes filles le soin de déclarer cette fonction, car elle diffère selon
    // la forme générale du bâtiment (carrée, circulaire, ...)
    virtual void generateBuilding() = 0;
    Building(int minh, int maxh, int minw, int maxw);
    int getHeight();
    int getWidth();
};

#endif // BUILDING_H
