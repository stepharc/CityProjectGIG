#include "factory.h"

#include "squaredbuilding.h"
#include "circularbuilding.h"

#include <iostream>

Factory::Factory(QVector3D center) : Building(1, 5, 5, 10, 5, 10, center)
{
    int prob = rand() % 101;
    if(prob >= 0 && prob <= 49){
        std::cout << "Squared Factory (" << prob << ")" << std::endl;
        shapeGeometry = new SquaredBuilding(getWidth(), getHeight(), getDepth(), center);
    }else{
        std::cout << "Cylinder Factory (" << prob << ")" << std::endl;
        shapeGeometry = new CircularBuilding(getWidth(), getHeight(), getDepth(), center);
    }
}
