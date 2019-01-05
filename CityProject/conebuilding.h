#ifndef CONEBUILDING_H
#define CONEBUILDING_H

#include "building.h"
#include "basegeometry.h"

// Désigne les bâtiments de forme générale cylindrique.

class ConeBuilding : public baseGeometry
{
private :

public:
    ConeBuilding(int width, int height, int depth, QVector3D center);
    void initGeometry();
};

#endif // CONEBUILDING_H
