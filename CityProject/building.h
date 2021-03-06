#ifndef BUILDING_H
#define BUILDING_H

#include "basegeometry.h"

#include <QVector3D>

// Mother class for all building types.

class Building
{
protected :
    int height;
    int width;
    int depth;
    baseGeometry * shapeGeometry;
    QVector3D centerPos; //Position of center of building.
public :
    Building(int minh, int maxh, int minw, int maxw, int minp, int maxp, QVector3D center);
    int getHeight(){ return height; }
    int getWidth(){ return width; }
    int getDepth(){ return depth; }
    baseGeometry * getShapeGeometry(){ return shapeGeometry; }
    QVector3D getCenterPos(){ return centerPos; }
};

#endif // BUILDING_H
