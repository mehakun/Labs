#include <QMouseEvent>
#include <cmath>

#include <MyWidget.hpp>

static const char *vertex_shader = R"(
                                   #version 130

                                   uniform mat4 mvp_matrix;

                                   attribute vec3 a_position;

                                   out vec3 vertex_color;
                                   out vec3 fragVert;
                                   out vec3 fragNormal;

                                   void main()
                                   {

                                   vertex_color = vec3(2.0, 2.0, 8.0);
                                   fragVert = a_position;
                                   fragNormal = normalize(a_position);
                                   // Calculate vertex position in screen space
                                   gl_Position = mvp_matrix * vec4(a_position, 1.0);


                                   }
                                   )";
static const char *fragment_shader = R"(
                                     #version 130

                                     in vec3 vertex_color;

                                     uniform struct Light {
                                        vec3 position;
                                        vec3 intensities; //a.k.a the color of the light
                                        float ambientCoefficient;
                                        float attenuation;
                                     } light;

                                     uniform mat4 model;
                                     uniform mat3 normalMatrix;

                                     uniform vec3 materialSpecularColor;
                                     uniform float materialShininess;

                                     in vec3 fragNormal;
                                     in vec3 fragVert;

                                     out vec4 frag_color;

                                     void main() {
                                     // calculate normal in world coordinates

                                     vec3 normal = normalize(normalMatrix * fragNormal);

                                     // calculate the location of this fragment (pixel) in world coordinates
                                     vec3 surfacePos = vec3(model * vec4(fragVert, 1));

                                     // surfaces to stuff
                                     vec3 surfaceToLight = normalize(light.position - surfacePos);
                                     vec3 surfaceToCamera = normalize(surfacePos);

                                     // diffuse light
                                     float diffuseCoefficient = max(0.0, dot(normal, surfaceToLight));
                                     vec3 diffuse = diffuseCoefficient * vertex_color * light.intensities;

                                     // ambient light
                                     vec3 ambient = sin(light.ambientCoefficient) * vertex_color * light.intensities;

                                     // specular light
                                     float specularCoefficient = 0.0;
                                     if (diffuseCoefficient > 0.0)
                                         specularCoefficient = pow(max(0.0, dot(surfaceToCamera, reflect(-surfaceToLight, normal))), materialShininess);
                                     vec3 specular = specularCoefficient * materialSpecularColor * light.intensities;

                                     // attenuation
                                     float distanceToLight = length(light.position - surfacePos);
                                     float attenuation = 1.0 / (1.0 + light.attenuation * pow(distanceToLight, 2));

                                     frag_color = vec4(ambient + attenuation * (diffuse + specular), 1.0);
                                     }
                                     )";

MyWidget::MyWidget(QWidget *parent) :
    QOpenGLWidget(parent), geometries(nullptr), texture(nullptr),
    angularSpeed(0), zoom_scale(1.0), approx_scale(4),
    light(QVector3D(), QVector3D(1, 1, 1), 0.2f, 0.5f),
    materialSpecularColor(1.0f, 1.0f, 1.0f), materialShininess(50.0f)
{
    setFocusPolicy(Qt::StrongFocus);
}

void MyWidget::onApproxChange(int value)
{

    approx_scale = value;
    update();
}

void MyWidget::onBrightChange(int value)
{
    auto coord = value / qreal(100);
    light.intensities = QVector3D(coord, coord, coord);
    update();
}

void MyWidget::onAmbientChange()
{
    light.ambientCoeff = std::fmod(light.ambientCoeff + 0.05, M_PI);
    update();
}

void MyWidget::onShineChange(int value)
{
    materialShininess = value;
    update();
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

    // Set BG color to black
    glClearColor(0, 0, 0, 1);

    glShadeModel(GL_SMOOTH);
    initShaders();

    // Enable depth buffer
    glEnable(GL_DEPTH_TEST);

    // Enable back face culling
    glEnable(GL_CULL_FACE);

    // Enable lightning
    glEnable(GL_LIGHTING);

    // Enable color-driven materials
    glEnable(GL_COLOR_MATERIAL);

    // Enable one source of light
    glEnable(GL_LIGHT0);

    glEnable(GL_COLOR_MATERIAL);

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

    // set modelview matrix
    program.setUniformValue("model", matrix);

    // set light's position to camera's one
    light.position = -matrix.inverted() * QVector3D(1, 1, 1) ;

    // set normal matrix(inversed and transposed)
    program.setUniformValue("normalMatrix", matrix.normalMatrix());

    // Set modelview-projection matrix
    program.setUniformValue("mvp_matrix", projection * matrix);

    // Draw pyramid
    geometries->drawGeometry(&program, approx_scale, light, materialSpecularColor, materialShininess);
}

MyWidget::~MyWidget()
{
    makeCurrent();

    delete texture;
    delete geometries;

    doneCurrent();
}
