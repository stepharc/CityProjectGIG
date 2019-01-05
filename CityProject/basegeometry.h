#ifndef BASEGEOMETRY_H
#define BASEGEOMETRY_H

#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>

class baseGeometry : protected QOpenGLFunctions
{
public:
    struct VertexData
    {
        QVector3D position;
        QVector2D texCoord;
    };

    baseGeometry(QString vsp, QString fsp, QVector3D center, QVector3D scale);
    virtual ~baseGeometry();

    void initGL();
    bool prepareShaderProgram();

    void parseObjFile(const QString &fileName, std::vector<VertexData> &vdata);
    void drawGeometry();

    QOpenGLShaderProgram shaderProgram;
    QVector3D getCenterModel(){ return centerModel; }
    QVector3D getScaleModel(){ return scaleModel; }

protected:
    virtual void initGeometry();
    void initGeometryWithOBJFile(const QString &fileName);

    QString vertexShaderPath;
    QString fragShaderPath;

    QOpenGLBuffer arrayBuf;
    QOpenGLBuffer indexBuf;
    int indexBufSize;

    QVector3D centerModel;
    QVector3D scaleModel;
};

#endif // BASEGEOMETRY_H
