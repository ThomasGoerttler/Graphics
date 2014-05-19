#pragma once

#include <QGLWidget>
#include <QtOpenGL>
#ifdef __APPLE__
#include <OpenGL/GLU.h>
#else
#include <GL/glu.h>
#endif

#include <QMatrix4x4>

#include "abstractexercise.h"

class QBasicTimer;
class QTimerEvent;

class AbstractGLExercise : public AbstractExercise, public QGLWidget
{
public:
    AbstractGLExercise(QWidget * parent = NULL);
    virtual ~AbstractGLExercise();

    virtual void initializeGL();
    virtual void paintGL() = 0;

    virtual void resizeGL(int width, int height);

    virtual void enable();
    virtual void disable();

    static const GLuint loadTexture(const QString & filePath);

    static void drawUnitCube(const QMatrix4x4 & transform);
    static void drawUnitCube(GLuint & list, const QMatrix4x4 & transform);

    static void drawUnitBase();
    static void drawUnitBase(GLuint & list);

protected:
    void timerEvent(QTimerEvent * event);

protected:
    QBasicTimer * m_timer;

    QMatrix4x4 m_projection;
    QMatrix4x4 m_view;

    uint m_frame;
};
