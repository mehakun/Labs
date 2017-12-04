#ifndef GEOMETRYENGINE_HPP
#define GEOMETRYENGINE_HPP

#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>
#include <vector>
#include <utility>

class GeometryEngine : protected QOpenGLFunctions
{
public:
    GeometryEngine(int radius = 1, int height = 2, unsigned int curr_approx_points = 4);
    virtual ~GeometryEngine();

    void drawGeometry(QOpenGLShaderProgram *program, unsigned int approx_points,
                      const std::pair<QVector3D, QVector3D> &light, GLfloat ambientCoeff);

private:
    void initGeometry();
    void initVertices();
    void triangulizeBotTop();
    unsigned int triangulize(unsigned int start_vertice,
                     unsigned int center,
                     unsigned int end_vertice_ind,
                     unsigned int vertex_ind,
                     bool is_wall);
    int radius;
    int height;
    unsigned int curr_approx_points;
    unsigned int indeces_amount;
    QOpenGLBuffer indexBuf;
    QOpenGLBuffer arrayBuf;
    std::vector<QVector3D> vertices;
    std::vector<GLuint> indeces;
};

#endif // GEOMETRYENGINE_HPP
