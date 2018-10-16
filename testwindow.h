#ifndef TESTWINDOW_H
#define TESTWINDOW_H

#include <QImage>
#include <QApplication>
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

    private:
        GLuint texture[1]; //On charge une seule texture
};

#endif // TESTWINDOW_H
