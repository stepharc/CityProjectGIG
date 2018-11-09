#include "baseglwidget.h"

baseGLWidget::baseGLWidget(int framesPerSecond, QWidget *parent, char *name)
    : QGLWidget(parent)
{
    setWindowTitle(QString::fromUtf8(name));
    if(framesPerSecond == 0)
        t_Timer = NULL;
    else
    {
        int seconde = 1000; // 1 seconde = 1000 ms
        int timerInterval = seconde / framesPerSecond;
        t_Timer = new QTimer(this);
        connect(t_Timer, SIGNAL(timeout()), this, SLOT(timeOutSlot()));
        t_Timer->start( timerInterval );
    }
    fullscreen = false;
}

//Active le mode plein-écran si la fenêtre est en mode fenêtrée et vice-versa.
void baseGLWidget::toggleFullscreen()
{
    if(fullscreen)
    {
        showNormal();
        fullscreen = false;
    }
    else
    {
        showFullScreen();
        fullscreen = true;
    }
}

void baseGLWidget::keyPressEvent(QKeyEvent *keyEvent)
{
    switch(keyEvent->key())
    {
        case Qt::Key_Escape:
            close();
            break;
        case Qt::Key_F1:
            toggleFullscreen();
            break;
    }
}

//Remplacement de gluPerspective
void baseGLWidget::perspectiveGL( GLdouble fovY, GLdouble aspect, GLdouble zNear, GLdouble zFar )
{
    const GLdouble pi = 3.1415926535897932384626433832795;
    GLdouble fW, fH;

    fH = tan( fovY / 360 * pi ) * zNear;
    fW = fH * aspect;

    glFrustum( -fW, fW, -fH, fH, zNear, zFar );
}

//Cette fonction est appelée framesPerSecond (paramètre du constructeur de classe)
//fois par seconde.
void baseGLWidget::timeOutSlot()
{
    //appel à paintGL
    updateGL();
}
