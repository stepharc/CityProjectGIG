#ifndef HOUSE_H
#define HOUSE_H

#include "squaredbuilding.h"

class House : public SquaredBuilding
{
private :
public:
    House(QVector3D center);
};

#endif // HOUSE_H
