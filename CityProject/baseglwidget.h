#ifndef BASEGLWIDGET_H
#define BASEGLWIDGET_H

#include "basegeometry.h"

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLBuffer>
#include <QOpenGLShaderProgram>
#include <QKeyEvent>
#include <QBasicTimer>

class baseGLWidget : public QOpenGLWidget, protected QOpenGLFunctions
{
 Q_OBJECT
public:
    baseGLWidget(std::vector<baseGeometry *> & glist, QWidget* parent = nullptr );

protected:
    virtual void initializeGL();
    virtual void resizeGL( int w, int h );
    virtual void paintGL();
    virtual void keyPressEvent( QKeyEvent* e );
    void timerEvent(QTimerEvent* e);

private:
    std::vector<baseGeometry *> geos_;
    QBasicTimer timer_;

    float rotateAngleY_;
    QVector3D cameraPos_;
    QVector3D cameraTarget_;
    QMatrix4x4 projection_;
};

#endif // BASEGLWIDGET_H
