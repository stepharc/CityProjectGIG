#include "periphery.h"

Periphery::Periphery(int c, int r, float rsw, float rsd) :
    District(c, r, rsw, rsd)
{
    probHouse = 85;
    probFactory = 15;
    probTower = 0;
    generateBuilding();
}
