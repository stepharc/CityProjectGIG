#ifndef CIRCULARBUILDING_H
#define CIRCULARBUILDING_H

#include "building.h"
#include "basegeometry.h"

// Désigne les bâtiments de forme générale cylindrique.

class CircularBuilding : public baseGeometry
{
private :

public:
    CircularBuilding(int width, int height, int depth, QVector3D center);
    void initGeometry();
};

#endif // CIRCULARBUILDING_H
