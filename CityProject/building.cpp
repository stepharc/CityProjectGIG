#include "building.h"

#include <iostream>

Building::Building(int minh, int maxh, int minw, int maxw, int minp, int maxp, QVector3D center) : centerPos(center)
{
    height = rand() % (maxh - minh) + minh;
    width = rand() % (maxw - minw) + minw;
    depth = rand() % (maxp - minp) + minp;
    std::cout << "Hauteur : " << height << ", Largeur : " << width << ", Profondeur : " << depth << std::endl;
}
