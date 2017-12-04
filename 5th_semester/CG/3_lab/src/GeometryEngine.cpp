#include <GeometryEngine.hpp>

#include <QVector2D>
#include <QVector3D>
#include <cmath>
#include <utility>

GeometryEngine::GeometryEngine(int radius, int height, unsigned int curr_approx_points)
    : radius(radius), height(height), curr_approx_points(curr_approx_points),
      indexBuf(QOpenGLBuffer::IndexBuffer), vertices({QVector3D(0, 0, 0), QVector3D(0, 0, height)}),
      indeces()
{
    initializeOpenGLFunctions();

    // Generate 2 buffers
    arrayBuf.create();
    indexBuf.create();

    // Initializes geometry and transfers it to buffers
    initGeometry();
}

GeometryEngine::~GeometryEngine()
{
    arrayBuf.destroy();
    indexBuf.destroy();
}

void GeometryEngine::drawGeometry(QOpenGLShaderProgram *program, unsigned int approx_points,
                                  const std::pair<QVector3D, QVector3D> &light, GLfloat ambientCoeff)
{
    // remake approximation if current one isn't needed by user
    if (approx_points != curr_approx_points) {
        curr_approx_points = approx_points;
        qDebug() << "Resizing GeometryEngine's vectors to" << curr_approx_points;
        initGeometry();
    }

    // Tell OpenGL which buffers to use
    arrayBuf.bind();
    indexBuf.bind();

    // Tell OpenGL programmable pipeline how to locate vertex position data
    int vertexLocation = program->attributeLocation("a_position");
    program->enableAttributeArray(vertexLocation);
    program->setAttributeBuffer(vertexLocation, GL_FLOAT, 0, 3, sizeof(QVector3D));

    // set diffuse light settings
    program->setUniformValue("light.position", light.first);
    program->setUniformValue("light.intensities", light.second);

    // set ambient coeff
    program->setUniformValue("light.ambientCoefficient", ambientCoeff);

    // Draw pyramid geometry using indeces from second buffer
    glDrawElements(GL_TRIANGLE_STRIP, indeces_amount, GL_UNSIGNED_INT, nullptr);
}

void GeometryEngine::initGeometry()
{
    initVertices();
    if (indeces.size() < 16 * curr_approx_points + 6) {
        indeces.insert(indeces.cend(), 16 * curr_approx_points + 6 - indeces.size(), 0);
    }

    // triangulize bottom
    indeces_amount = triangulize(2, 0, curr_approx_points + 1, 0, false);

    // triangulize top
    indeces_amount = triangulize(2 + curr_approx_points, 1, 2 * curr_approx_points + 1, indeces_amount, false);

    // triangulize walls
    indeces_amount = triangulize(2, 0, curr_approx_points + 2, indeces_amount, true);

    // Triangle strips can be connected by duplicating indeces
    // between the strips. If connecting strips have opposite
    // vertex order then last index of the first strip and first
    // index of the second strip needs to be duplicated. If
    // connecting strips have same vertex order then only last
    // index of the first strip needs to be duplicated.

    // Transfer vertex data to VBO 0
    arrayBuf.bind();
    arrayBuf.allocate(vertices.data(), vertices.size() * sizeof(QVector3D));

    // Transfer index data to VBO 1
    indexBuf.bind();
    indexBuf.allocate(indeces.data(), indeces_amount * sizeof(GLuint));
}

void
GeometryEngine::initVertices()
{
    unsigned int vertex_ind = 2;
    unsigned int i = 0;

    // Vertex data for cylinder approximation (bottom)
    for (; i < curr_approx_points && vertex_ind < vertices.size(); ++vertex_ind, ++i) {
        vertices[vertex_ind] = QVector3D(radius * std::cos(2 * M_PI * i / curr_approx_points),
                                         radius * std::sin(2 * M_PI * i / curr_approx_points),
                                         0);
    }

    // if vector's capacity isn't enough we need to allocate place for new elements
    for (; i < curr_approx_points; ++i, ++vertex_ind) {
        vertices.emplace_back(radius * std::cos(2 * M_PI * i / curr_approx_points),
                              radius * std::sin(2 * M_PI * i / curr_approx_points),
                              0);

    }

    i = 0;

    // Vertex data for cylinder approximation (top)
    for (; i < curr_approx_points && vertex_ind < vertices.size(); ++vertex_ind, ++i) {
        vertices[vertex_ind] = QVector3D(radius * std::cos(2 * M_PI * i / curr_approx_points),
                                         radius * std::sin(2 * M_PI * i / curr_approx_points),
                                         height);
    }

    // if vector's capacity isn't enough we need to allocate place for new elements
    for (; i < curr_approx_points; ++i) {
        vertices.emplace_back(radius * std::cos(2 * M_PI * i / curr_approx_points),
                              radius * std::sin(2 * M_PI * i / curr_approx_points),
                              height);
    }

}

unsigned int
GeometryEngine::triangulize(unsigned int start_vertice, unsigned int center,
                            unsigned int end_vertice_ind, unsigned int vertex_ind, bool is_wall)
{
    if (!is_wall) {
        // making triangulization of bottom\top side
        for (unsigned int k = start_vertice; k < end_vertice_ind; ++k, vertex_ind += 4) {
            indeces[vertex_ind] = k;
            indeces[vertex_ind + 1] = center;
            indeces[vertex_ind + 2] = k + 1;
            indeces[vertex_ind + 3] = k + 1;
        }

        // last triangle of convex polygon
        indeces[vertex_ind] = end_vertice_ind;
        indeces[++vertex_ind] = center;
        indeces[++vertex_ind] = start_vertice;

    } else {
        // building dem walls for dem cylinders
        for (unsigned int k = start_vertice; k < end_vertice_ind - 1; ++k, vertex_ind += 8) {
            indeces[vertex_ind] = k;
            indeces[vertex_ind + 1] = k + 1;
            indeces[vertex_ind + 2] = k + 1 + curr_approx_points;
            indeces[vertex_ind + 3] = k + 1 + curr_approx_points;

            indeces[vertex_ind + 4] = k;
            indeces[vertex_ind + 5] = k + 1 + curr_approx_points;
            indeces[vertex_ind + 6] = k + curr_approx_points;
            indeces[vertex_ind + 7] = k + curr_approx_points;
        }

        // last wall lol
        indeces[vertex_ind] = curr_approx_points + 1;
        indeces[++vertex_ind] = 2;
        indeces[++vertex_ind] = curr_approx_points + 2;
        indeces[++vertex_ind] = curr_approx_points + 2;

        indeces[++vertex_ind] = curr_approx_points + 1;
        indeces[++vertex_ind] = curr_approx_points + 2;
        indeces[++vertex_ind] = 2 * curr_approx_points + 1;
    }

    return vertex_ind + 1;
}
