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

#include <GeometryEngine.hpp>

class GeometryEngine;

class MyWidget : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT

public:
    explicit MyWidget(QWidget *parent = nullptr);
    ~MyWidget();

signals:
void drawOrtho(QTransform view);

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
};

#endif // MYWIDGET_HPP
