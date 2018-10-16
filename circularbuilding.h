#ifndef CIRCULARBUILDING_H
#define CIRCULARBUILDING_H

#include "building.h"

// Désigne les bâtiments de forme générale cylindrique.

class CircularBuilding : public Building
{
private :

public:
    void generateBuilding();
    CircularBuilding(int minh, int maxh, int minw, int maxw);
};

#endif // CIRCULARBUILDING_H
