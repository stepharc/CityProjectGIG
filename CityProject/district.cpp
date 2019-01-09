#include "district.h"

District::District(int c, int r, float rsw, float rsd) :
    colOnSurface(c),
    rowOnSurface(r),
    center(QVector3D((c * rsw) + (rsw / 2), 0, (r * rsd) + (rsd / 2))) // Center of area [c ; r] on city surface
{

}
