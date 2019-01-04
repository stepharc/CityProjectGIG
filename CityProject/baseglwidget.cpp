#include "baseglwidget.h"

#include <iostream>
#include <cmath>

baseGLWidget::baseGLWidget(std::vector<baseGeometry *> glist, QWidget* parent)
 : QOpenGLWidget( parent ),
   geos_(glist)
{
    float offset = 5;
    rotateAngleY_ = 0;
    cameraPos_ = QVector3D(0, 1, 0);
    cameraTarget_ = QVector3D(cameraPos_.x(), cameraPos_.y(), cameraPos_.z() - offset);
}

void baseGLWidget::timerEvent(QTimerEvent*){
    update();
}

void baseGLWidget::initializeGL()
{
    initializeOpenGLFunctions();

    // Set the clear color to blue
    glClearColor( 0.0f, 0.0f, 1.0f, 1.0f );

    // Don't forget to set up OpenGL context for objects to show,
    // since this widget's OpenGL context has been initialized.
    for(int i = 0; i < int(geos_.size()); i++){
        geos_.at(ulong(i))->initGL();
        geos_.at(ulong(i))->prepareShaderProgram();
    }

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

    timer_.start(12, this);
}

void baseGLWidget::resizeGL( int w, int h )
{
    // Calculate aspect ratio
    qreal aspect = qreal(w) / qreal(h ? h : 1);

    // Set near plane to 0.001, far plane to 1500.0, field of view 45 degrees
    const qreal zNear = 0.001, zFar = 1500.0, fov = 45.0;

    // Reset projection
    projection_.setToIdentity();

    // Set perspective projection
    projection_.perspective(fov, float(aspect), float(zNear), zFar);
}

void baseGLWidget::paintGL()
{
    // Clear the buffer with the current clearing color
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    QMatrix4x4 viewMatrix;
    viewMatrix.lookAt(
        cameraPos_,
        cameraTarget_,
        QVector3D(0, 1, 0)
    );
    viewMatrix.rotate(rotateAngleY_, 0, 1, 0);

    for(int i = 0; i < int(geos_.size()); i++){
        baseGeometry * geometry = geos_.at(ulong(i));

        // Calculate model view transformation
        // Model Matrix, translate at object's center
        QMatrix4x4 modelMatrix;
        modelMatrix.translate(geometry->getCenterModel());
        modelMatrix.scale(geometry->getScaleModel());

        // Bind the shader program so that we can associate variables from
        // our application to the shaders
        if ( !geometry->shaderProgram.bind() )
        {
            std::cout << "Could not bind shader program to context" << std::endl;
            return;
        }

        // Set modelview-projection matrix
        geometry->shaderProgram.setUniformValue("mvp_matrix", projection_ * viewMatrix * modelMatrix);

        // Draw stuff
        geometry->drawGeometry();
    }
}

void baseGLWidget::keyPressEvent( QKeyEvent* e )
{
    float pas = 0.1f, rotateSpeed = 0.8f;
    switch ( e->key() )
    {
        case Qt::Key_Escape:
            this->close();
            break;
        case Qt::Key_S: // Translate : Backward
            cameraPos_.setZ(cameraPos_.z() + pas);
            cameraTarget_.setZ(cameraTarget_.z() + pas);
            break;
        case Qt::Key_Z: // Translate : Forward
            cameraPos_.setZ(cameraPos_.z() - pas);
            cameraTarget_.setZ(cameraTarget_.z() - pas);
            break;
        case Qt::Key_D: // Translate : Right
            cameraPos_.setX(cameraPos_.x() + pas);
            cameraTarget_.setX(cameraTarget_.x() + pas);
            break;
        case Qt::Key_Q: // Translate : Left
            cameraPos_.setX(cameraPos_.x() - pas);
            cameraTarget_.setX(cameraTarget_.x() - pas);
            break;
        case Qt::Key_Up: // Translate : Up
            cameraPos_.setY(cameraPos_.y() + pas);
            cameraTarget_.setY(cameraTarget_.y() + pas);
            break;
        case Qt::Key_Down: // Translate : Down
            cameraPos_.setY(cameraPos_.y() - pas);
            cameraTarget_.setY(cameraTarget_.y() - pas);
            break;
        case Qt::Key_Right: // Rotate : Right
            rotateAngleY_ += rotateSpeed;
            break;
        case Qt::Key_Left: // Rotate : Left
            rotateAngleY_ -= rotateSpeed;
            break;
        default:
            QString keyText = QKeySequence(e->key()).toString();
            std::cout << keyText.toStdString() << " : button pressed." << std::endl;
            QOpenGLWidget::keyPressEvent( e );
    }
}
