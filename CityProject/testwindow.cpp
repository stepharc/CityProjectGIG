#include "testwindow.h"
#include "GL/glu.h"

testWindow::testWindow(QWidget *parent)
    : baseGLWidget(60, parent, "Building Test Window")
{
}

//Initialisation d'openGL
void testWindow::initializeGL()
{
    programID = loadShaders("shaders/testvertex.vert", "shaders/testfragment.frag");
    glShadeModel(GL_SMOOTH);
    glClearColor(0.7f, 0.9f, 1.0f, 1.0f);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
    loadTexture("texture/box.png");
    glEnable(GL_TEXTURE_2D);
}

//Fonction permettant de gérer le redimensionnement (changement résolution)
void testWindow::resizeGL(int width, int height)
{
    if(height == 0)
        height = 1;
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    perspectiveGL(45.0f, (GLfloat)width/(GLfloat)height, 0.1f, 100.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

//Permet d'afficher la scène openGL
void testWindow::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    static const GLfloat vbufferdata = build->generateBuilding(programID);
    GLuint vb = getVertexBuffer();
    int bl = build->getBufferLength();
    build->drawBuilding(vb, vbufferdata, bl);
    glFlush();
}

void testWindow::loadTexture(QString textureName)
{
    QImage qim_Texture;
    QImage qim_TempTexture;
    qim_TempTexture.load(textureName);
    qim_Texture = QGLWidget::convertToGLFormat( qim_TempTexture );
    glGenTextures( 1, &texture[0] );
    glBindTexture( GL_TEXTURE_2D, texture[0] );
    glTexImage2D( GL_TEXTURE_2D, 0, 3, qim_Texture.width(), qim_Texture.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, qim_Texture.bits() );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
}

void testWindow::loadBuilding(Building * h){
    build = h;
}
