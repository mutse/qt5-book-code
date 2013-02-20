#ifndef VOWELCUBE_H
#define VOWELCUBE_H

#include <QtOpenGL>
#include <QRadialGradient>

class VowelCube : public QGLWidget
{
    Q_OBJECT

public:
    VowelCube(QWidget *parent = 0);
    ~VowelCube();

protected:
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void wheelEvent(QWheelEvent *event);

private:
    void createGradient();
    void createGLObject();
    void drawBackground(QPainter *painter);
    void drawCube();
    void drawLegend(QPainter *painter);

    GLuint glObject;
    QRadialGradient gradient;
    GLfloat rotationX;
    GLfloat rotationY;
    GLfloat rotationZ;
    GLfloat scaling;
    QPoint lastPos;
};

#endif
