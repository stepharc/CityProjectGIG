#include "squaredbuilding.h"

SquaredBuilding::SquaredBuilding(int minh, int maxh, int minw, int maxw) : Building(minh, maxh, minw, maxw)
{

}

void SquaredBuilding::generateBuilding(){
    float posX = getSurfaceX();
    float posY = getSurfaceY();
    float posZ = getSurfaceZ();
    float minl = posX - (getWidth()/2), maxl = posX + (getWidth()/2);
    float minh = posY - (getHeight()/2), maxh = posY + (getHeight()/2);
    float minp = posZ - (getWidth()/2), maxp = posZ + (getWidth()/2);
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
