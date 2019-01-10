#include "downtown.h"

Downtown::Downtown(int c, int r, float rsw, float rsd) :
    District (c, r, rsw, rsd)
{
    probTower = 80;
    probHouse = 10;
    probFactory = 10;
    generateBuilding();
}
