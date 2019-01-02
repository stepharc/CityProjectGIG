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

    void drawGeometry(QOpenGLShaderProgram *program);

    QString getVertexShaderPath(){ return vertexShaderPath; }
    QString getFragShaderPath(){ return fragShaderPath; }
    QVector3D getCenterModel(){ return centerModel; }
    QVector3D getScaleModel(){ return scaleModel; }

protected:
    void initGeometry();

    QString vertexShaderPath;
    QString fragShaderPath;

    QOpenGLBuffer arrayBuf;
    QOpenGLBuffer indexBuf;

    QVector3D centerModel;
    QVector3D scaleModel;
};

#endif // BASEGEOMETRY_H
