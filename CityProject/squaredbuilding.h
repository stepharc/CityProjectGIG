#ifndef SQUAREDBUILDING_H
#define SQUAREDBUILDING_H

#include "building.h"
#include "GL/glu.h"

// Désigne tous les bâtiments de forme générale cubique.

class SquaredBuilding : public Building
{
private:
    float posX, posY, posZ; //Position of bottom face of cube, top left point on city area (= surface)
public:
    SquaredBuilding(int minh, int maxh, int minw, int maxw);
    void generateBuilding();
    void setSurfacePosition(float x, float y, float z);
};

#endif // SQUAREDBUILDING_H
