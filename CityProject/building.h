#ifndef BUILDING_H
#define BUILDING_H

#include <GL/glut.h>
#include <stdlib.h>
#include <QDebug>

// Classe mère de tous les types de bâtiments.

class Building
{
private :
    int height; // hauteur du bâtiment (m)
    int width;  // largeur du bâtiment (m)
    float posX, posY, posZ; //Position of center of building on city surface.
    int bufferLength;
public :
    // On laisse aux classes filles le soin de déclarer cette fonction, car elle diffère selon
    // la forme générale du bâtiment (carrée, circulaire, ...)
    virtual const GLfloat generateBuilding(GLuint programID) = 0;
    void drawBuilding(GLuint VertexBuffer, const GLfloat vbdata, int bufferLength);
    Building(int minh, int maxh, int minw, int maxw);
    int getHeight();
    int getWidth();
    float getSurfaceX();
    float getSurfaceY();
    float getSurfaceZ();
    void setSurfacePosition(float x, float y, float z);
    void setBufferLength(int b){ bufferLength = b; }
    int getBufferLength(){ return bufferLength; }
};

#endif // BUILDING_H
