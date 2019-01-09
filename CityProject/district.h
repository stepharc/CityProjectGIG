#ifndef DISTRICT_H
#define DISTRICT_H

#include "basegeometry.h"
#include <QVector3D>

class District
{
public:
    District(int c, int r, float rsw, float rsd);
    baseGeometry * getBuilding(){ return building; }

protected:
    int colOnSurface, rowOnSurface;
    QVector3D center;

    int probHouse, probTower, probFactory;
    baseGeometry * building;
    void generateBuilding();
};

#endif // DISTRICT_H
