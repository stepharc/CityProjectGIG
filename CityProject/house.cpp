#include "house.h"
#include "squaredbuilding.h"
#include "circularbuilding.h"

#include <iostream>

House::House(QVector3D center) : Building(1, 5, 1, 5, 1, 5, center)
{
    int prob = rand() % 101;
    if(prob >= 0 && prob <= 49){
        std::cout << "Squared House (" << prob << ")" << std::endl;
        shapeGeometry = new SquaredBuilding(getWidth(), getHeight(), getDepth(), center);
    }else{
        std::cout << "Cylinder House (" << prob << ")" << std::endl;
        shapeGeometry = new CircularBuilding(getWidth(), getHeight(), getDepth(), center);
    }
}
