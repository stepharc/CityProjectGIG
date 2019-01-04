#ifndef CIRCULARBUILDING_H
#define CIRCULARBUILDING_H

#include "building.h"
#include "basegeometry.h"

// Désigne les bâtiments de forme générale cylindrique.

class CircularBuilding : public Building, public baseGeometry
{
private :

public:
    CircularBuilding(int minh, int maxh, int minw, int maxw, int minp, int maxp, QVector3D center);
    void initGeometry();
};

#endif // CIRCULARBUILDING_H
