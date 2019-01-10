#include "district.h"
#include "house.h"
#include "factory.h"
#include "tower.h"

#include <iostream>

District::District(int c, int r, float rsw, float rsd) :
    colOnSurface(c),
    rowOnSurface(r),
    center(QVector3D(c * rsw, 0, r * rsd)) // Center of area [c ; r] on city surface
{
}

void District::generateBuilding(){
    if(probHouse + probTower + probFactory > 100) return;
    int prob = rand() % 101;
    if(prob >= 0 && prob <= probHouse){
        Building * b = new House(center);
        building = b->getShapeGeometry();
    }else{
        if(prob > probHouse && prob <= probHouse + probTower){
            Building * b = new Tower(center);
            building = b->getShapeGeometry();
        }else{
            Building * b = new Factory(center);
            building = b->getShapeGeometry();
        }
    }
}
