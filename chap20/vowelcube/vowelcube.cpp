#include <QtWidgets>
#include <cmath>

#ifndef GL_MULTISAMPLE
#define GL_MULTISAMPLE 0x809D
#endif

#include "vowelcube.h"

VowelCube::VowelCube(QWidget *parent)
    : QGLWidget(parent)
{
    setFormat(QGLFormat(QGL::SampleBuffers));

    rotationX = -38.0;
    rotationY = -58.0;
    rotationZ = 0.0;
    scaling = 1.0;

    createGradient();
    createGLObject();
}

VowelCube::~VowelCube()
{
    makeCurrent();
    glDeleteLists(glObject, 1);
}

void VowelCube::paintEvent(QPaintEvent * /* event */)
{
    QPainter painter(this);
    drawBackground(&painter);
    drawCube();
    drawLegend(&painter);
}

void VowelCube::mousePressEvent(QMouseEvent *event)
{
    lastPos = event->pos();
}

void VowelCube::mouseMoveEvent(QMouseEvent *event)
{
    GLfloat dx = GLfloat(event->x() - lastPos.x()) / width();
    GLfloat dy = GLfloat(event->y() - lastPos.y()) / height();

    if (event->buttons() & Qt::LeftButton) {
        rotationX += 180 * dy;
        rotationY += 180 * dx;
        update();
    } else if (event->buttons() & Qt::RightButton) {
        rotationX += 180 * dy;
        rotationZ += 180 * dx;
        update();
    }
    lastPos = event->pos();
}

void VowelCube::wheelEvent(QWheelEvent *event)
{
    double numDegrees = -event->delta() / 8.0;
    double numSteps = numDegrees / 15.0;
    scaling *= std::pow(1.125, numSteps);
    update();
}

void VowelCube::createGradient()
{
    gradient.setCoordinateMode(QGradient::ObjectBoundingMode);
    gradient.setCenter(0.45, 0.50);
    gradient.setFocalPoint(0.40, 0.45);
    gradient.setColorAt(0.0, QColor(105, 146, 182));
    gradient.setColorAt(0.4, QColor(81, 113, 150));
    gradient.setColorAt(0.8, QColor(16, 56, 121));
}

void VowelCube::createGLObject()
{
    makeCurrent();

    glShadeModel(GL_FLAT);

    glObject = glGenLists(1);
    glNewList(glObject, GL_COMPILE);
    qglColor(QColor(255, 239, 191));
    glLineWidth(1.0);

    glBegin(GL_LINES);
    glVertex3f(+1.0, +1.0, -1.0);
    glVertex3f(-1.0, +1.0, -1.0);
    glVertex3f(+1.0, -1.0, -1.0);
    glVertex3f(-1.0, -1.0, -1.0);
    glVertex3f(+1.0, -1.0, +1.0);
    glVertex3f(-1.0, -1.0, +1.0);
    glEnd();

    glBegin(GL_LINE_LOOP);
    glVertex3f(+1.0, +1.0, +1.0);
    glVertex3f(+1.0, +1.0, -1.0);
    glVertex3f(+1.0, -1.0, -1.0);
    glVertex3f(+1.0, -1.0, +1.0);
    glVertex3f(+1.0, +1.0, +1.0);
    glVertex3f(-1.0, +1.0, +1.0);
    glVertex3f(-1.0, +1.0, -1.0);
    glVertex3f(-1.0, -1.0, -1.0);
    glVertex3f(-1.0, -1.0, +1.0);
    glVertex3f(-1.0, +1.0, +1.0);
    glEnd();

    glEndList();
}

void VowelCube::drawBackground(QPainter *painter)
{
    painter->setPen(Qt::NoPen);
    painter->setBrush(gradient);
    painter->drawRect(rect());
}

void VowelCube::drawCube()
{
    glPushAttrib(GL_ALL_ATTRIB_BITS);

    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    GLfloat x = 3.0 * GLfloat(width()) / height();
    glOrtho(-x, +x, -3.0, +3.0, 4.0, 15.0);

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
    glTranslatef(0.0, 0.0, -10.0);
    glScalef(scaling, scaling, scaling);

    glRotatef(rotationX, 1.0, 0.0, 0.0);
    glRotatef(rotationY, 0.0, 1.0, 0.0);
    glRotatef(rotationZ, 0.0, 0.0, 1.0);

    glEnable(GL_MULTISAMPLE);

    glCallList(glObject);

    setFont(QFont("Times", 24));
    qglColor(QColor(255, 223, 127));

    renderText(+1.1, +1.1, +1.1, QChar('a'));
    renderText(-1.1, +1.1, +1.1, QChar('e'));
    renderText(+1.1, +1.1, -1.1, QChar('o'));
    renderText(-1.1, +1.1, -1.1, QChar(0x00F6));
    renderText(+1.1, -1.1, +1.1, QChar(0x0131));
    renderText(-1.1, -1.1, +1.1, QChar('i'));
    renderText(+1.1, -1.1, -1.1, QChar('u'));
    renderText(-1.1, -1.1, -1.1, QChar(0x00FC));

    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();

    glMatrixMode(GL_PROJECTION);
    glPopMatrix();

    glPopAttrib();
}

void VowelCube::drawLegend(QPainter *painter)
{
    const int Margin = 11;
    const int Padding = 6;

    QTextDocument textDocument;
    textDocument.setDefaultStyleSheet("* { color: #FFEFEF }");
    textDocument.setHtml("<h4 align=\"center\">Vowel Categories</h4>"
                         "<p align=\"center\"><table width=\"100%\">"
                         "<tr><td>Open:<td>a<td>e<td>o<td>&ouml;"
                         "<tr><td>Close:<td>&#305;<td>i<td>u<td>&uuml;"
                         "<tr><td>Front:<td>e<td>i<td>&ouml;<td>&uuml;"
                         "<tr><td>Back:<td>a<td>&#305;<td>o<td>u"
                         "<tr><td>Round:<td>o<td>&ouml;<td>u<td>&uuml;"
                         "<tr><td>Unround:<td>a<td>e<td>&#305;<td>i"
                         "</table>");
    textDocument.setTextWidth(textDocument.size().width());

    QRect rect(QPoint(0, 0), textDocument.size().toSize()
                             + QSize(2 * Padding, 2 * Padding));
    painter->translate(width() - rect.width() - Margin,
                       height() - rect.height() - Margin);
    painter->setPen(QColor(255, 239, 239));
    painter->setBrush(QColor(255, 0, 0, 31));
    painter->drawRect(rect);

    painter->translate(Padding, Padding);
    textDocument.drawContents(painter);
}
