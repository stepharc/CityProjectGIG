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

float Building::getSurfaceX(){
    return posX;
}

float Building::getSurfaceY(){
    return posY;
}

float Building::getSurfaceZ(){
    return posZ;
}

void Building::setSurfacePosition(float x, float y, float z){
    posX = x;
    posY = y;
    posZ = z;
}
