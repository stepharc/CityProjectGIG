#include "squaredbuilding.h"

SquaredBuilding::SquaredBuilding(int minh, int maxh, int minw, int maxw) : Building(minh, maxh, minw, maxw)
{

}

void SquaredBuilding::generateBuilding(){
    float minl = posX, maxl = posX + getWidth();
    float minh = posY, maxh = posY + getHeight();
    float minp = posZ, maxp = posZ + getWidth();
    glLoadIdentity();
    glColor3f(0.5,0.5,0.5);

    //Drawing cube
    glBegin(GL_QUADS);
    // top
        glVertex3f(minl, maxh, maxp);
        glVertex3f(maxl, maxh, maxp);
        glVertex3f(maxl, maxh, minp);
        glVertex3f(minl, maxh, minp);
    glEnd();

    glBegin(GL_QUADS);
    // front
        glVertex3f(maxl, minh, maxp);
        glVertex3f(maxl, maxh, maxp);
        glVertex3f(minl, maxh, maxp);
        glVertex3f(minl, minh, maxp);
    glEnd();

    glBegin(GL_QUADS);
    // right
        glVertex3f(maxl, maxh, minp);
        glVertex3f(maxl, maxh, maxp);
        glVertex3f(maxl, minh, maxp);
        glVertex3f(maxl, minh, minp);
    glEnd();

    glBegin(GL_QUADS);
    // left
        glVertex3f(minl, minh, maxp);
        glVertex3f(minl, maxh, maxp);
        glVertex3f(minl, maxh, minp);
        glVertex3f(minl, minh, minp);
    glEnd();

    glBegin(GL_QUADS);
    // bottom
        glVertex3f(maxl, minh, maxp);
        glVertex3f(minl, minh, maxp);
        glVertex3f(minl, minh, minp);
        glVertex3f(maxl, minh, minp);
    glEnd();

    glBegin(GL_QUADS);
    // back
        glVertex3f(maxl, maxh, minp);
        glVertex3f(maxl, minh, minp);
        glVertex3f(minl, minh, minp);
        glVertex3f(minl, maxh, minp);
    glEnd();
}

void SquaredBuilding::setSurfacePosition(float x, float y, float z){
    posX = x;
    posY = y;
    posZ = z;
}
