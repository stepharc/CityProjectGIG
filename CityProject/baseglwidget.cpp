#include "baseglwidget.h"
#include <sstream>
#include <fstream>

baseGLWidget::baseGLWidget(int framesPerSecond, QWidget *parent, char *name)
    : QGLWidget(parent)
{
    setWindowTitle(QString::fromUtf8(name));
    if(framesPerSecond == 0)
        t_Timer = nullptr;
    else
    {
        int seconde = 1000; // 1 seconde = 1000 ms
        int timerInterval = seconde / framesPerSecond;
        t_Timer = new QTimer(this);
        connect(t_Timer, SIGNAL(timeout()), this, SLOT(timeOutSlot()));
        t_Timer->start( timerInterval );
    }
    fullscreen = false;
    camXpos = 0.;
    camZpos = -50.;
    camXangle = 0;
    camYangle = 45;
    glGenVertexArrays(1, &VertexArrayID);
    glBindVertexArray(VertexArrayID);
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

void baseGLWidget::translateCamera(int key, int valueModifier){
    switch(key){
        case Qt::Key_Z:
            camZpos += valueModifier;
            break;
        case Qt::Key_S:
            camZpos -= valueModifier;
            break;
        case Qt::Key_Q:
            camXpos += valueModifier;
            break;
        case Qt::Key_D:
            camXpos -= valueModifier;
            break;
    }
    moveCamera();
}

void baseGLWidget::rotateCamera(int key, int valueModifier){
    switch(key){
        case Qt::Key_F:
            camXangle -= valueModifier;
            break;
        case Qt::Key_R:
            camXangle += valueModifier;
            break;
        case Qt::Key_A:
            camYangle += valueModifier;
            break;
        case Qt::Key_E:
            camYangle -= valueModifier;
            break;
    }
    moveCamera();
}

void baseGLWidget::moveCamera(){
    // On efface les pixels de l'image (color buffer) et le Z-Buffer (depth buffer).
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // On initialise la matrice de vue avec la matrice identité.
    glLoadIdentity();

    // On applique une translation et une rotation à la scène pour simuler
    // un déplacement de caméra.
    glTranslatef(camXpos, 0, camZpos);
    glRotatef(camXangle, 1, 0, 0);
    glRotatef(camYangle, 0, 1, 0);

    // On force OpenGL à afficher avant de passer à la suite.
    glFlush();
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
        //Camera Translation
        case Qt::Key_Z:
            translateCamera(keyEvent->key(), 1);
            break;
        case Qt::Key_S:
            translateCamera(keyEvent->key(), 1);
            break;
        case Qt::Key_Q:
            translateCamera(keyEvent->key(), 1);
            break;
        case Qt::Key_D:
            translateCamera(keyEvent->key(), 1);
            break;
        //Camera Rotation
        case Qt::Key_A:
            rotateCamera(keyEvent->key(), 1);
            break;
        case Qt::Key_E:
            rotateCamera(keyEvent->key(), 1);
            break;
        case Qt::Key_R:
            rotateCamera(keyEvent->key(), 1);
            break;
        case Qt::Key_F:
            rotateCamera(keyEvent->key(), 1);
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

GLuint baseGLWidget::loadShaders(const char * vertex_file_path, const char * fragment_file_path){

    // Create the shaders
    GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
    GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

    // Read the Vertex Shader code from the file
    std::string VertexShaderCode;
    std::ifstream VertexShaderStream(vertex_file_path, std::ios::in);
    if(VertexShaderStream.is_open()){
        std::stringstream sstr;
        sstr << VertexShaderStream.rdbuf();
        VertexShaderCode = sstr.str();
        VertexShaderStream.close();
    }else{
        printf("Impossible to open %s. Are you in the right directory ? Don't forget to read the FAQ !\n", vertex_file_path);
        getchar();
        return 0;
    }

    // Read the Fragment Shader code from the file
    std::string FragmentShaderCode;
    std::ifstream FragmentShaderStream(fragment_file_path, std::ios::in);
    if(FragmentShaderStream.is_open()){
        std::stringstream sstr;
        sstr << FragmentShaderStream.rdbuf();
        FragmentShaderCode = sstr.str();
        FragmentShaderStream.close();
    }

    GLint Result = GL_FALSE;
    int InfoLogLength;

    // Compile Vertex Shader
    printf("Compiling shader : %s\n", vertex_file_path);
    char const * VertexSourcePointer = VertexShaderCode.c_str();
    glShaderSource(VertexShaderID, 1, &VertexSourcePointer , nullptr);
    glCompileShader(VertexShaderID);

    // Check Vertex Shader
    glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &Result);
    glGetShaderiv(VertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
    if ( InfoLogLength > 0 ){
        std::vector<char> VertexShaderErrorMessage(InfoLogLength+1);
        glGetShaderInfoLog(VertexShaderID, InfoLogLength, nullptr, &VertexShaderErrorMessage[0]);
        printf("%s\n", &VertexShaderErrorMessage[0]);
    }

    // Compile Fragment Shader
    printf("Compiling shader : %s\n", fragment_file_path);
    char const * FragmentSourcePointer = FragmentShaderCode.c_str();
    glShaderSource(FragmentShaderID, 1, &FragmentSourcePointer , nullptr);
    glCompileShader(FragmentShaderID);

    // Check Fragment Shader
    glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &Result);
    glGetShaderiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
    if ( InfoLogLength > 0 ){
        std::vector<char> FragmentShaderErrorMessage(InfoLogLength+1);
        glGetShaderInfoLog(FragmentShaderID, InfoLogLength, nullptr, &FragmentShaderErrorMessage[0]);
        printf("%s\n", &FragmentShaderErrorMessage[0]);
    }

    // Link the program
    printf("Linking program\n");
    GLuint ProgramID = glCreateProgram();
    glAttachShader(ProgramID, VertexShaderID);
    glAttachShader(ProgramID, FragmentShaderID);
    glLinkProgram(ProgramID);

    // Check the program
    glGetProgramiv(ProgramID, GL_LINK_STATUS, &Result);
    glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);
    if ( InfoLogLength > 0 ){
        std::vector<char> ProgramErrorMessage(InfoLogLength+1);
        glGetProgramInfoLog(ProgramID, InfoLogLength, nullptr, &ProgramErrorMessage[0]);
        printf("%s\n", &ProgramErrorMessage[0]);
    }

    glDetachShader(ProgramID, VertexShaderID);
    glDetachShader(ProgramID, FragmentShaderID);

    glDeleteShader(VertexShaderID);
    glDeleteShader(FragmentShaderID);

    return ProgramID;
}

