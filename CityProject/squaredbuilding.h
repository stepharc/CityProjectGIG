#ifndef SQUAREDBUILDING_H
#define SQUAREDBUILDING_H

#include "building.h"
#include "GL/glu.h"

// Désigne tous les bâtiments de forme générale cubique.

class SquaredBuilding : public Building
{
private:
public:
    SquaredBuilding(int minh, int maxh, int minw, int maxw);
    void generateBuilding(GLuint programID);
};

#endif // SQUAREDBUILDING_H
