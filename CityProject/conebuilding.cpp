#include "conebuilding.h"

ConeBuilding::ConeBuilding(int width, int height, int depth, QVector3D center)
     : baseGeometry("../shaders/basevertex.vert", "../shaders/cone.frag", center, QVector3D(width, height, depth))
{
}

void ConeBuilding::initGeometry()
{
    initGeometryWithOBJFile("../objs/blendcone.obj");
}
