#ifndef SQUAREDBUILDING_H
#define SQUAREDBUILDING_H

#include "building.h"
#include "basegeometry.h"

class SquaredBuilding : public baseGeometry
{
private:
public:
    SquaredBuilding(int width, int height, int depth, QVector3D center);
};

#endif // SQUAREDBUILDING_H
