#ifndef BASEGLWIDGET_H
#define BASEGLWIDGET_H


#include <QtOpenGL>
#include <QGLWidget>

class baseGLWidget : public QGLWidget
{
    Q_OBJECT
public:
    explicit baseGLWidget(int framesPerSecond = 0, QWidget *parent = 0, char *name = 0);
    virtual void initializeGL() = 0;
    virtual void resizeGL(int width, int height) = 0;
    virtual void paintGL() = 0;
    virtual void keyPressEvent( QKeyEvent *keyEvent );
    void perspectiveGL( GLdouble fovY, GLdouble aspect, GLdouble zNear, GLdouble zFar );
    void toggleFullscreen();

public slots:
    virtual void timeOutSlot();

private:
    QTimer *t_Timer;
    bool fullscreen;

};

#endif // BASEGLWIDGET_H
