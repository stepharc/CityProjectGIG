#ifndef HOUSE_H
#define HOUSE_H

#include "building.h"

class House : public Building
{
private :
public:
    House(QVector3D center);
};

#endif // HOUSE_H
