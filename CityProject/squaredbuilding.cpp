#include "squaredbuilding.h"
#include <GLES3/gl3.h>

SquaredBuilding::SquaredBuilding(int minh, int maxh, int minw, int maxw) : Building(minh, maxh, minw, maxw)
{
    setBufferLength(12*3);
}

/*void SquaredBuilding::generateBuilding(){
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
}*/

const GLfloat SquaredBuilding::generateBuilding(GLuint programID){
    float posX = getSurfaceX();
    float posY = getSurfaceY();
    float posZ = getSurfaceZ();
    float minl = posX - (getWidth()/2), maxl = posX + (getWidth()/2);
    float minh = posY - (getHeight()/2), maxh = posY + (getHeight()/2);
    float minp = posZ - (getWidth()/2), maxp = posZ + (getWidth()/2);
    glUseProgram(programID);
    static const GLfloat g_vertex_buffer_data[] = {
        minl,minh,minp, // triangle 1 : begin
        minl,minh, maxp,
        minl, maxh, maxp, // triangle 1 : end
        maxl, maxh,minp, // triangle 2 : begin
        minl,minh,minp,
        minl, maxh,minp, // triangle 2 : end
        maxl,minh, maxp,
        minl,minh,minp,
        maxl,minh,minp,
        maxl, maxh,minp,
        maxl,minh,minp,
        minl,minh,minp,
        minl,minh,minp,
        minl, maxh, maxp,
        minl, maxh,minp,
        maxl,minh, maxp,
        minl,minh, maxp,
        minl,minh,minp,
        minl, maxh, maxp,
        minl,minh, maxp,
        maxl,minh, maxp,
        maxl, maxh, maxp,
        maxl,minh,minp,
        maxl, maxh,minp,
        maxl,minh,minp,
        maxl, maxh, maxp,
        maxl,minh, maxp,
        maxl, maxh, maxp,
        maxl, maxh,minp,
        minl, maxh,minp,
        maxl, maxh, maxp,
        minl, maxh,minp,
        minl, maxh, maxp,
        maxl, maxh, maxp,
        minl, maxh, maxp,
        maxl,minh, maxp
    };
    return g_vertex_buffer_data;
}
