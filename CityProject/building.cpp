#include "building.h"
#include <GLES3/gl3.h>

Building::Building(int minh, int maxh, int minw, int maxw)
{
    height = rand() % (maxh - minh) + minh;
    width = rand() % (maxw - minw) + minw;
    qDebug("Hauteur : %d, Largeur : %d\n", height, width);
}

int Building::getHeight(){
    return height;
}

int Building::getWidth(){
    return width;
}

float Building::getSurfaceX(){
    return posX;
}

float Building::getSurfaceY(){
    return posY;
}

float Building::getSurfaceZ(){
    return posZ;
}

void Building::setSurfacePosition(float x, float y, float z){
    posX = x;
    posY = y;
    posZ = z;
}

void Building::drawBuilding(GLuint VertexBuffer, const GLfloat vbdata, int bufferLength){
    // Give our vertices to OpenGL.
    glBufferData(GL_ARRAY_BUFFER, sizeof(vbdata), vbdata, GL_STATIC_DRAW);
    // 1st attribute buffer : vertices
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, VertexBuffer);
    glVertexAttribPointer(
       0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
       bufferLength,       // size
       GL_FLOAT,           // type
       GL_FALSE,           // normalized?
       0,                  // stride
       nullptr            // array buffer offset
    );
    // Draw the triangle !
    glDrawArrays(GL_TRIANGLES, 0, bufferLength);
    glDisableVertexAttribArray(0);
}
