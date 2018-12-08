#ifndef TESTWINDOW_H
#define TESTWINDOW_H

#include <QImage>
#include "baseglwidget.h"
#include "tower.h"
#include "house.h"

class testWindow : public baseGLWidget
{
    Q_OBJECT
    public:
        explicit testWindow(QWidget *parent = 0);
        void initializeGL();
        void resizeGL(int width, int height);
        void paintGL();
        void loadTexture(QString texturename);
        void loadBuilding(Building * h);
        GLuint getProgramID(){ return programID; }

    private:
        GLuint texture[1]; //On charge une seule texture
        Building * build;
        GLuint programID;
};

#endif // TESTWINDOW_H
