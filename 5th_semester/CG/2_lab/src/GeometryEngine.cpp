#include <GeometryEngine.hpp>

#include <QVector2D>
#include <QVector3D>
#include <cmath>

GeometryEngine::GeometryEngine(int outerRadius, int height)
    : R(outerRadius), height(height), indexBuf(QOpenGLBuffer::IndexBuffer)
{
    initializeOpenGLFunctions();

    // Generate 2 buffers
    arrayBuf.create();
    indexBuf.create();

    // Initializes Pyramid geometry and transfers it to buffers
    initPyramidGeometry();
}

GeometryEngine::~GeometryEngine()
{
    arrayBuf.destroy();
    indexBuf.destroy();
}

void GeometryEngine::drawPyramidGeometry(QOpenGLShaderProgram *program)
{
    // Tell OpenGL which buffers to use
    arrayBuf.bind();
    indexBuf.bind();

    // Tell OpenGL programmable pipeline how to locate vertex position data
    int vertexLocation = program->attributeLocation("a_position");
    program->enableAttributeArray(vertexLocation);
    program->setAttributeBuffer(vertexLocation, GL_FLOAT, 0, 3, sizeof(QVector3D));

    int lineLocation = program->uniformLocation("line");

    program->setUniformValue(lineLocation, false);

    // Draw pyramid geometry using indices from second buffer
    glDrawElements(GL_TRIANGLE_STRIP, 39, GL_UNSIGNED_SHORT, nullptr);


    // Draw edges on pyramid derp
    program->setUniformValue(lineLocation, true);
    glDrawElements(GL_LINE_STRIP, 19, GL_UNSIGNED_SHORT, nullptr);

    auto error = glGetError();

    if (error != GL_NO_ERROR) {
        qDebug() << "what" << error;
    }
}

void GeometryEngine::initPyramidGeometry()
{
    // For Pyramid need 7 vertices
    QVector3D vertices[7];

    // Vertex data for bottom
    for (int i = 0; i < 5; ++i) {
        vertices[i] = QVector3D(R * std::cos(2 * M_PI * i / 5), R * std::sin(2 * M_PI * i / 5), 0);
    }

    // Vertex data for bottom's center
    vertices[5] = QVector3D(0, 0, 0);

    // Vertex data for top of the pyramid
    vertices[6] = QVector3D(0, 0, height);

    // Indices for drawing Pyramid faces using triangle strips.
    // Triangle strips can be connected by duplicating indices
    // between the strips. If connecting strips have opposite
    // vertex order then last index of the first strip and first
    // index of the second strip needs to be duplicated. If
    // connecting strips have same vertex order then only last
    // index of the first strip needs to be duplicated.
    GLushort indices[] = {
        // triangles that form pyramid's triangles that are connected to it's top
        0, 1, 6, 6,
        1, 2, 6, 6,
        2, 3, 6, 6,
        3, 4, 6, 6,
        4, 0, 6,
        // triangles that form pyramid's bottom
        0, 1, 5, 5,
        1, 2, 5, 5,
        2, 3, 5, 5,
        3, 4, 5, 5,
        4, 0, 5, 5
    };

    // Transfer vertex data to VBO 0
    arrayBuf.bind();
    arrayBuf.allocate(vertices, 7 * sizeof(QVector3D));

    // Transfer index data to VBO 1
    indexBuf.bind();
    indexBuf.allocate(indices, 39 * sizeof(GLushort));
}

