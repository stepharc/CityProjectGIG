#include "building.h"

Building::Building(int minh, int maxh, int minw, int maxw)
{
    height = rand() % (maxh - minh) + minh;
    width = rand() % (maxw - minw) + minw;
    qDebug("Hauteur : %d, Largeur : %d\n", height, width);
}

int Building::getHeight(){
    return height;
}

int Building::getWidth(){
    return width;
}
