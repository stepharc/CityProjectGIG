#ifndef PERIPHERY_H
#define PERIPHERY_H

#include "district.h"

class Periphery : public District
{
public:
    Periphery(int c, int r, float rsw, float rsd);
};

#endif // PERIPHERY_H
