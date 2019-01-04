#include "baseglwidget.h"

#include <iostream>
#include <cmath>
#include <QCoreApplication>

baseGLWidget::baseGLWidget(QWidget* parent )
 : QOpenGLWidget( parent )
{
    cameraPos_ = QVector3D();
}

void baseGLWidget::timerEvent(QTimerEvent*){
    update();
}

void baseGLWidget::initializeGL()
{
    initializeOpenGLFunctions();

    // Set the clear color to blue
    glClearColor( 0.0f, 0.0f, 1.0f, 1.0f );

    QString vsp = "../shaders/basevertex.vert";
    QString fsp = "../shaders/basefrag.frag";
    geometries_ = new baseGeometry(vsp, fsp, QVector3D(1, 1, -4), QVector3D(1, 1, 2));

    // Prepare a complete shader program… (NEED PARAMETERS HERE)
    if ( !prepareShaderProgram( geometries_->getVertexShaderPath(), geometries_->getFragShaderPath() ) ){
        return;
    }

    // Bind the shader program so that we can associate variables from
    // our application to the shaders
    if ( !shaderProgram_.bind() )
    {
        std::cout << "Could not bind shader program to context" << std::endl;
        return;
    }

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

    timer_.start(12, this);
}

bool baseGLWidget::prepareShaderProgram( const QString& vertexShaderPath,
 const QString& fragmentShaderPath )
{
    // First we load and compile the vertex shader…
    bool result = shaderProgram_.addShaderFromSourceFile( QOpenGLShader::Vertex, vertexShaderPath );
    if ( !result ) qWarning() << shaderProgram_.log() ;


    // …now the fragment shader…
    result = shaderProgram_.addShaderFromSourceFile( QOpenGLShader::Fragment, fragmentShaderPath );
    if ( !result ) qWarning() << shaderProgram_.log();

    // … we link them to shader pipeline in order to resolve any references.
    result = shaderProgram_.link();
    if ( !result ) qWarning() << "Could not link shader program:" << shaderProgram_.log();

    return result;
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
    projection_.perspective(fov, aspect, zNear, zFar);
}

void baseGLWidget::paintGL()
{
    // Clear the buffer with the current clearing color
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    // Calculate model view transformation
    // Model Matrix, translate at object's center
    // Scale : X -> width, Y -> height, Z-> depth.
    QMatrix4x4 modelMatrix;
    modelMatrix.translate(geometries_->getCenterModel());
    modelMatrix.scale(geometries_->getScaleModel());

    QMatrix4x4 viewMatrix;
    viewMatrix.lookAt(
        cameraPos_,
        geometries_->getCenterModel(),
        QVector3D(0, 1, 0)
    );

    // Set modelview-projection matrix
    shaderProgram_.setUniformValue("mvp_matrix", projection_ * viewMatrix * modelMatrix);

    // Draw stuff
    geometries_->drawGeometry(&shaderProgram_);
}

void baseGLWidget::keyPressEvent( QKeyEvent* e )
{
    float pas = 0.1f;
    switch ( e->key() )
    {
        case Qt::Key_Escape:
            QCoreApplication::instance()->quit();
            break;
        case Qt::Key_S: // Translate : Backward
            cameraPos_.setZ(cameraPos_.z() + pas);
            break;
        case Qt::Key_Z: // Translate : Forward
            cameraPos_.setZ(cameraPos_.z() - pas);
            break;
        case Qt::Key_D: // Translate : Right
            cameraPos_.setX(cameraPos_.x() + pas);
            break;
        case Qt::Key_Q: // Translate : Left
            cameraPos_.setX(cameraPos_.x() - pas);
            break;
        case Qt::Key_Up: // Translate : Up
            cameraPos_.setY(cameraPos_.y() + pas);
            break;
        case Qt::Key_Down: // Translate : Down
            cameraPos_.setY(cameraPos_.y() - pas);
            break;
        default:
            QString keyText = QKeySequence(e->key()).toString();
            std::cout << keyText.toStdString() << " : button pressed." << std::endl;
            QOpenGLWidget::keyPressEvent( e );
    }
}
