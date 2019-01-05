#include "squaredbuilding.h"

SquaredBuilding::SquaredBuilding(int width, int height, int depth, QVector3D center)
    : baseGeometry("../shaders/basevertex.vert", "../shaders/square.frag", center, QVector3D(width, height, depth))
{
}
