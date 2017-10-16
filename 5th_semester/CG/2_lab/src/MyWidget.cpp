#include <QMouseEvent>
#include <cmath>

#include <MyWidget.hpp>

static const char *vertex_shader = R"(
                                   #version 130
                                   #ifdef GL_ES
                                   // Set default precision to medium
                                   precision mediump int;
                                   precision mediump float;
                                   #endif

                                   uniform mat4 mvp_matrix;
                                   attribute vec4 a_position;
                                   uniform bool line;
                                   out vec3 vertex_color;

                                   void main()
                                   {
                                   if (line) {
                                    vertex_color=vec3(0.0,0.0,0.0);
                                   } else {
                                    vertex_color=vec3(255.0, 255.0, 255.0);
                                   }

                                   // Calculate vertex position in screen space
                                   gl_Position = mvp_matrix * a_position;
                                   }
                                   )";
static const char *fragment_shader = R"(
                                     #version 130
                                     #ifdef GL_ES
                                     // Set default precision to medium
                                     precision mediump int;
                                     precision mediump float;
                                     #endif

                                     in vec3 vertex_color;
                                     out vec4 frag_color;

                                     void main()
                                     {
                                     frag_color=vec4(vertex_color,1.0);
                                     }
                                     )";

MyWidget::MyWidget(QWidget *parent) :
    QOpenGLWidget(parent), geometries(nullptr), texture(nullptr), angularSpeed(0), zoom_scale(1.0)
{
    setFocusPolicy(Qt::StrongFocus);
}

void MyWidget::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_Minus:
        zoom_scale /= 1.1;
        update();
        break;
    case Qt::Key_Plus:
        zoom_scale *= 1.1;
        update();
        break;
    default:
        QOpenGLWidget::keyPressEvent(event);
        break;
    }
}

void MyWidget::mousePressEvent(QMouseEvent *e)
{
    // Save mouse press position
    mousePressPosition = QVector2D(e->localPos());
}

void MyWidget::mouseReleaseEvent(QMouseEvent *e)
{

    // Mouse release position and mouse press position difference vector
    QVector2D diff = QVector2D(e->localPos()) - mousePressPosition;

    // Rotation axis is perpendicular to the mouse position difference vector
    QVector3D norm = QVector3D(diff.y(), diff.x(), 0.0).normalized();

    // Accelerate angular speed relative to the length of the mouse sweep
    qreal acc = diff.length() / 100.0;

    // Calculate new rotation axis as weighted sum
    rotationAxis = (rotationAxis * angularSpeed + norm * acc).normalized();

    // Increase angular speed
    angularSpeed += acc;
}

void MyWidget::timerEvent(QTimerEvent *e)
{
    // Decrease angular speed (friction)
    angularSpeed *= 0.99;

    // Stop rotation when speed goes below threshold
    if (angularSpeed < 0.01) {
        angularSpeed = 0.0;
    } else {
        // Update rotation
        rotation = QQuaternion::fromAxisAndAngle(rotationAxis, angularSpeed) * rotation;

        // Request an update
        update();
    }
}

void MyWidget::initializeGL()
{
    initializeOpenGLFunctions();

    // Set BG color to white
    glClearColor(255, 255, 255, 1);

    initShaders();

    // Enable depth buffer
    glEnable(GL_DEPTH_TEST);

    // Enable back face culling
    glEnable(GL_CULL_FACE);



    geometries = new GeometryEngine{};

    timer.start(12, this);
}

void MyWidget::initShaders()
{
    // Compile vertex shader
    if (!program.addShaderFromSourceCode(QOpenGLShader::Vertex, vertex_shader))
        close();

    // Compile fragment shader
    if (!program.addShaderFromSourceCode(QOpenGLShader::Fragment, fragment_shader))
        close();

    // Link shader pipeline
    if (!program.link())
        close();

    // Bind shader pipeline for use
    if (!program.bind())
        close();
}


void MyWidget::resizeGL(int width, int height)
{
    // Reset projection
    projection.setToIdentity();

    // calculate aspect ratio
    const qreal aspect_r = qreal(width) / qreal(height ? height : 1);

    // Set near plane to 3.0, far plane to 7.0, field of view 45 degrees
    const qreal zNear = 3.0;
    const qreal zFar = 7.0;
    const qreal fov = 45.0;

    // Set perspective projection
    projection.perspective(fov, aspect_r, zNear, zFar);
    //    } else {
//        qDebug() << "resizing for ortho";

//        //glViewport(0, 0, width, height);

//        const auto aratio = float(width) / float(height);
//        projection.ortho(-aratio, aratio, -1.0f, 1.0f, -1.0f, 1.0f);
//    }
}

void MyWidget::paintGL()
{
    // Clear color and depth buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Calculate model view transformation
    QMatrix4x4 matrix;

    matrix.translate(0.0, 0.0, -5.0);
    matrix.scale(zoom_scale, zoom_scale, zoom_scale);
    matrix.rotate(rotation);

    // Set modelview-projection matrix
    program.setUniformValue("mvp_matrix", projection * matrix);

    // Draw pyramid geometry
    geometries->drawPyramidGeometry(&program);
}

MyWidget::~MyWidget()
{
    makeCurrent();

    delete texture;
    delete geometries;

    doneCurrent();
}
