#ifndef BASEGLWIDGET_H
#define BASEGLWIDGET_H

#include <GL/glut.h>
#include <QtOpenGL>
#include <QGLWidget>
#include <GLES3/gl3.h>

class baseGLWidget : public QGLWidget
{
    Q_OBJECT
public:
    explicit baseGLWidget(int framesPerSecond = 0, QWidget *parent = nullptr, char *name = nullptr);
    virtual void initializeGL() = 0;
    virtual void resizeGL(int width, int height) = 0;
    virtual void paintGL() = 0;
    virtual void keyPressEvent( QKeyEvent *keyEvent );
    void perspectiveGL( GLdouble fovY, GLdouble aspect, GLdouble zNear, GLdouble zFar );
    void toggleFullscreen();
    void translateCamera(int key, int valueModifier);
    void rotateCamera(int key, int valueModifier);
    void moveCamera();
    GLuint loadShaders(const char * vertex_file_path,const char * fragment_file_path);
    GLuint getVertexBuffer(){ return VertexBuffer; }

public slots:
    virtual void timeOutSlot();

private:
    QTimer *t_Timer;
    bool fullscreen;
    float camXpos, camZpos; // For camera translation purpose
    int camXangle, camYangle; // For camera rotation purpose
    GLuint VertexArrayID; // Vertex Array Object
    GLuint VertexBuffer;
};

#endif // BASEGLWIDGET_H
