#include "circularbuilding.h"

#include <iostream>

CircularBuilding::CircularBuilding(int width, int height, int depth, QVector3D center)
     : baseGeometry("../shaders/basevertex.vert", "../shaders/cylinder.frag", center, QVector3D(width, height, depth))
{
}

void CircularBuilding::initGeometry()
{
    initGeometryWithOBJFile("../objs/blendcylinder.obj");
}
