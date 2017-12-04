#ifndef MYWIDGET_HPP
#define MYWIDGET_HPP
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QMatrix4x4>
#include <QQuaternion>
#include <QVector2D>
#include <QBasicTimer>
#include <QOpenGLShaderProgram>
#include <QOpenGLTexture>
#include <QTransform>
#include <utility>

#include <GeometryEngine.hpp>
#include <Light.hpp>

class GeometryEngine;

class MyWidget : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT

public:
    explicit MyWidget(QWidget *parent = nullptr);
    ~MyWidget();

public slots:
    void onApproxChange(int value);
    void onBrightChange(int value);
    void onAmbientChange();
    void onShineChange(int value);

protected:
    void keyPressEvent(QKeyEvent *event) override;
    void mousePressEvent(QMouseEvent *e) override;
    void mouseReleaseEvent(QMouseEvent *e) override;
    void timerEvent(QTimerEvent *e) override;
    void initializeGL() override;
    void resizeGL(int width, int height) override;
    void paintGL() override;

    virtual void initShaders();

private:
    QBasicTimer timer;
    QOpenGLShaderProgram program;
    GeometryEngine *geometries;

    QOpenGLTexture *texture;

    QMatrix4x4 projection;

    QVector2D mousePressPosition;
    QVector3D rotationAxis;
    qreal angularSpeed;
    QQuaternion rotation;
    qreal zoom_scale;
    int approx_scale;

    Light light;

    QVector3D materialSpecularColor;
    GLfloat materialShininess;
};

#endif // MYWIDGET_HPP
