#include "basegeometry.h"

#include <QVector2D>
#include <QVector3D>
#include <QFile>
#include <QRegularExpression>

baseGeometry::baseGeometry(QString vsp, QString fsp, QVector3D center, QVector3D scale)
    : indexBuf(QOpenGLBuffer::IndexBuffer),
      vertexShaderPath(vsp),
      fragShaderPath(fsp),
      centerModel(center),
      scaleModel(scale)
{
}

//Source : http://amin-ahmadi.com/2017/01/04/how-to-read-wavefront-obj-files-using-cqt/
void baseGeometry::parseObjFile(const QString &fileName, std::vector<VertexData> &vdata)
{
    QFile file(fileName);
    if(file.exists())
    {
        if(file.open(QFile::ReadOnly | QFile::Text))
        {
            std::vector<QVector3D> v;
            std::vector<QVector3D> triangles;
            std::vector<QVector2D> vt;

            while(!file.atEnd())
            {
                QString line = file.readLine().trimmed();
                QStringList lineParts = line.split(QRegularExpression("\\s+"));
                if(lineParts.count() > 0)
                {
                    // if it’s a vertex position (v)
                    if(lineParts.at(0).compare("v", Qt::CaseInsensitive) == 0)
                    {
                        v.push_back(QVector3D(lineParts.at(1).toFloat(),
                        lineParts.at(2).toFloat(),
                        lineParts.at(3).toFloat()));
                    }

                    // if it’s a texture (vt)
                    else if(lineParts.at(0).compare("vt", Qt::CaseInsensitive) == 0)
                    {
                        vt.push_back(QVector2D(lineParts.at(1).toFloat(),
                        lineParts.at(2).toFloat()));
                    }

                    // if it’s face data (f)
                    // there’s an assumption here that faces are all triangles
                    else if(lineParts.at(0).compare("f", Qt::CaseInsensitive) == 0)
                    {
                        // get points from v array
                        triangles.push_back(v.at(lineParts.at(1).split("/").at(0).toInt() - 1));
                        triangles.push_back(v.at(lineParts.at(2).split("/").at(0).toInt() - 1));
                        triangles.push_back(v.at(lineParts.at(3).split("/").at(0).toInt() - 1));
                    }
                }
            }
            file.close();
            QVector2D defaultTex = QVector2D(0,0);
            for(ulong i = 0 ; i < triangles.size(); i++){
                if(i >= vt.size()){
                    vdata.push_back({triangles.at(i), defaultTex});
                }else{
                    vdata.push_back({triangles.at(i), vt.at(i)});
                }
            }
        }
    }
}

baseGeometry::~baseGeometry()
{
    arrayBuf.destroy();
    indexBuf.destroy();
}

void baseGeometry::initGL(){
    initializeOpenGLFunctions();

    // Generate 2 VBOs
    arrayBuf.create();
    indexBuf.create();

    // Initializes cube geometry and transfers it to VBOs
    initGeometry();
}

bool baseGeometry::prepareShaderProgram()
{
    // First we load and compile the vertex shader…
    bool result = shaderProgram.addShaderFromSourceFile( QOpenGLShader::Vertex, vertexShaderPath );
    if ( !result ) qWarning() << shaderProgram.log() ;


    // …now the fragment shader…
    result = shaderProgram.addShaderFromSourceFile( QOpenGLShader::Fragment, fragShaderPath );
    if ( !result ) qWarning() << shaderProgram.log();

    // … we link them to shader pipeline in order to resolve any references.
    result = shaderProgram.link();
    if ( !result ) qWarning() << "Could not link shader program:" << shaderProgram.log();

    return result;
}

void baseGeometry::initGeometry()
{
    // For cube we would need only 8 vertices but we have to
    // duplicate vertex for each face because texture coordinate
    // is different.
    VertexData vertices[] = {
        // Vertex data for face 0
        {QVector3D(-1.0f, -1.0f,  1.0f), QVector2D(0.0f, 0.0f)},  // v0
        {QVector3D( 1.0f, -1.0f,  1.0f), QVector2D(0.33f, 0.0f)}, // v1
        {QVector3D(-1.0f,  1.0f,  1.0f), QVector2D(0.0f, 0.5f)},  // v2
        {QVector3D( 1.0f,  1.0f,  1.0f), QVector2D(0.33f, 0.5f)}, // v3

        // Vertex data for face 1
        {QVector3D( 1.0f, -1.0f,  1.0f), QVector2D( 0.0f, 0.5f)}, // v4
        {QVector3D( 1.0f, -1.0f, -1.0f), QVector2D(0.33f, 0.5f)}, // v5
        {QVector3D( 1.0f,  1.0f,  1.0f), QVector2D(0.0f, 1.0f)},  // v6
        {QVector3D( 1.0f,  1.0f, -1.0f), QVector2D(0.33f, 1.0f)}, // v7

        // Vertex data for face 2
        {QVector3D( 1.0f, -1.0f, -1.0f), QVector2D(0.66f, 0.5f)}, // v8
        {QVector3D(-1.0f, -1.0f, -1.0f), QVector2D(1.0f, 0.5f)},  // v9
        {QVector3D( 1.0f,  1.0f, -1.0f), QVector2D(0.66f, 1.0f)}, // v10
        {QVector3D(-1.0f,  1.0f, -1.0f), QVector2D(1.0f, 1.0f)},  // v11

        // Vertex data for face 3
        {QVector3D(-1.0f, -1.0f, -1.0f), QVector2D(0.66f, 0.0f)}, // v12
        {QVector3D(-1.0f, -1.0f,  1.0f), QVector2D(1.0f, 0.0f)},  // v13
        {QVector3D(-1.0f,  1.0f, -1.0f), QVector2D(0.66f, 0.5f)}, // v14
        {QVector3D(-1.0f,  1.0f,  1.0f), QVector2D(1.0f, 0.5f)},  // v15

        // Vertex data for face 4
        {QVector3D(-1.0f, -1.0f, -1.0f), QVector2D(0.33f, 0.0f)}, // v16
        {QVector3D( 1.0f, -1.0f, -1.0f), QVector2D(0.66f, 0.0f)}, // v17
        {QVector3D(-1.0f, -1.0f,  1.0f), QVector2D(0.33f, 0.5f)}, // v18
        {QVector3D( 1.0f, -1.0f,  1.0f), QVector2D(0.66f, 0.5f)}, // v19

        // Vertex data for face 5
        {QVector3D(-1.0f,  1.0f,  1.0f), QVector2D(0.33f, 0.5f)}, // v20
        {QVector3D( 1.0f,  1.0f,  1.0f), QVector2D(0.66f, 0.5f)}, // v21
        {QVector3D(-1.0f,  1.0f, -1.0f), QVector2D(0.33f, 1.0f)}, // v22
        {QVector3D( 1.0f,  1.0f, -1.0f), QVector2D(0.66f, 1.0f)}  // v23
    };

    // Indices for drawing cube faces using triangle strips.
    // Triangle strips can be connected by duplicating indices
    // between the strips. If connecting strips have opposite
    // vertex order then last index of the first strip and first
    // index of the second strip needs to be duplicated. If
    // connecting strips have same vertex order then only last
    // index of the first strip needs to be duplicated.
    GLushort indices[] = {
         0,  1,  2,  3,  3,     // Face 0 - triangle strip ( v0,  v1,  v2,  v3)
         4,  4,  5,  6,  7,  7, // Face 1 - triangle strip ( v4,  v5,  v6,  v7)
         8,  8,  9, 10, 11, 11, // Face 2 - triangle strip ( v8,  v9, v10, v11)
        12, 12, 13, 14, 15, 15, // Face 3 - triangle strip (v12, v13, v14, v15)
        16, 16, 17, 18, 19, 19, // Face 4 - triangle strip (v16, v17, v18, v19)
        20, 20, 21, 22, 23      // Face 5 - triangle strip (v20, v21, v22, v23)
    };

    // Transfer vertex data to VBO 0
    arrayBuf.bind();
    arrayBuf.allocate(vertices, 24 * sizeof(VertexData));

    indexBufSize = 34;
    // Transfer index data to VBO 1
    indexBuf.bind();
    indexBuf.allocate(indices, indexBufSize * sizeof(GLushort));
}

void baseGeometry::initGeometryWithOBJFile(const QString &fileName)
{
    std::vector<VertexData> vdata;
    std::vector<GLushort> indexes;

    parseObjFile(fileName, vdata);

    VertexData vertices[vdata.size()];
    std::copy(vdata.begin(), vdata.end(), vertices);

    for(ulong i = 0; i < vdata.size(); i++){
        indexes.push_back(GLushort(i));
    }

    GLushort indices[indexes.size()];
    std::copy(indexes.begin(), indexes.end(), indices);

    arrayBuf.bind();
    arrayBuf.allocate(vertices, int(vdata.size() * sizeof(VertexData)));

    indexBufSize = int(indexes.size());
    indexBuf.bind();
    indexBuf.allocate(indices, int(indexBufSize * sizeof(GLushort)));
}

void baseGeometry::drawGeometry()
{
    // Tell OpenGL which VBOs to use
    arrayBuf.bind();
    indexBuf.bind();

    // Offset for position
    quintptr offset = 0;

    // Tell OpenGL programmable pipeline how to locate vertex position data
    int vertexLocation = shaderProgram.attributeLocation("a_position");
    shaderProgram.enableAttributeArray(vertexLocation);
    shaderProgram.setAttributeBuffer(vertexLocation, GL_FLOAT, int(offset), 3, sizeof(VertexData));

    // Offset for texture coordinate
    //offset += sizeof(QVector3D);

    // Tell OpenGL programmable pipeline how to locate vertex texture coordinate data
    /*int texcoordLocation = program->attributeLocation("a_texcoord");
    program->enableAttributeArray(texcoordLocation);
    program->setAttributeBuffer(texcoordLocation, GL_FLOAT, offset, 2, sizeof(VertexData));*/

    // Draw cube geometry using indices from VBO 1
    glDrawElements(GL_TRIANGLE_STRIP, indexBufSize, GL_UNSIGNED_SHORT, nullptr);
}
