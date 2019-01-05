#include "tower.h"
#include "squaredbuilding.h"
#include "circularbuilding.h"
#include "conebuilding.h"

#include <iostream>

Tower::Tower(QVector3D center) : Building(5, 20, 1, 5, 1, 5, center)
{
    int prob = rand() % 101;
    if(prob >= 0 && prob <= 33){
        std::cout << "Squared Tower (" << prob << ")" << std::endl;
        shapeGeometry = new SquaredBuilding(getWidth(), getHeight(), getDepth(), center);
    }else{
        if(prob >= 34 && prob <= 66){
            std::cout << "Cylinder Tower (" << prob << ")" << std::endl;
            shapeGeometry = new CircularBuilding(getWidth(), getHeight(), getDepth(), center);
        }else{
            std::cout << "Cone Tower (" << prob << ")" << std::endl;
            shapeGeometry = new ConeBuilding(getWidth(), getHeight(), getDepth(), center);
        }
    }
}
