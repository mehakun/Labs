#ifndef GEOMETRYENGINE_HPP
#define GEOMETRYENGINE_HPP

#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>

class GeometryEngine : protected QOpenGLFunctions
{
public:
    GeometryEngine(int outerRadius = 1, int height = 2);
    virtual ~GeometryEngine();

    void drawPyramidGeometry(QOpenGLShaderProgram *program);

private:
    void initPyramidGeometry();

    int R;
    int height;
    QOpenGLBuffer indexBuf;
    QOpenGLBuffer arrayBuf;

};

#endif // GEOMETRYENGINE_HPP
