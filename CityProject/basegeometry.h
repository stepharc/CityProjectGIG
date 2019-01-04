#ifndef BASEGEOMETRY_H
#define BASEGEOMETRY_H

#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>

class baseGeometry : protected QOpenGLFunctions
{
public:
    baseGeometry(QString vsp, QString fsp, QVector3D center, QVector3D scale);
    virtual ~baseGeometry();

    void initGL();
    bool prepareShaderProgram();

    void drawGeometry();

    QOpenGLShaderProgram shaderProgram;
    QVector3D getCenterModel(){ return centerModel; }
    QVector3D getScaleModel(){ return scaleModel; }

    struct VertexData
    {
        QVector3D position;
        QVector2D texCoord;
    };

protected:
    virtual void initGeometry();

    QString vertexShaderPath;
    QString fragShaderPath;

    QOpenGLBuffer arrayBuf;
    QOpenGLBuffer indexBuf;

    QVector3D centerModel;
    QVector3D scaleModel;
};

#endif // BASEGEOMETRY_H
