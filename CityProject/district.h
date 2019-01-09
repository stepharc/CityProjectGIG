#ifndef DISTRICT_H
#define DISTRICT_H

#include <QVector3D>

class District
{
public:
    District(int c, int r, float rsw, float rsd);

protected:
    int colOnSurface, rowOnSurface;
    QVector3D center;
};

#endif // DISTRICT_H
