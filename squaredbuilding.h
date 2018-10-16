#ifndef SQUAREDBUILDING_H
#define SQUAREDBUILDING_H

#include "building.h"

// Désigne tous les bâtiments de forme générale cubique.

class SquaredBuilding : public Building
{
private:

public:
    void generateBuilding();
    SquaredBuilding(int minh, int maxh, int minw, int maxw);
};

#endif // SQUAREDBUILDING_H
