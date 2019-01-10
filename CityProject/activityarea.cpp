#include "activityarea.h"

ActivityArea::ActivityArea(int c, int r, float rsw, float rsd) :
    District (c, r, rsw, rsd)
{
    probHouse = 15;
    probFactory = 85;
    probTower = 0;
    generateBuilding();
}
