#ifndef LIGHT_HPP
#define LIGHT_HPP

#include <QVector3D>
#include <QOpenGLFunctions>

struct Light
{
    Light() = default;
    Light(const QVector3D &p, const QVector3D &i, GLfloat at, GLfloat am)
        : position(p), intensities(i), attenuation(at), ambientCoeff(am)
    {

    };

    ~Light() = default;

    QVector3D position;
    QVector3D intensities;
    GLfloat attenuation;
    GLfloat ambientCoeff;
};
#endif // LIGHT_HPP
