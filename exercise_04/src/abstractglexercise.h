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
class ThreeDObject;

enum ProjectionMode
{
    Perspective,
    OrthoFront,
    OrthoBack,
    OrthoTop,
    OrthoLeft,
    OrthoRight
};

class AbstractGLExercise : public QGLWidget, public AbstractExercise
{
    Q_OBJECT

public:
    AbstractGLExercise(float animationFrame = 0.0f, QWidget * parent = NULL);
    virtual ~AbstractGLExercise();

    virtual void initializeGL();
    virtual void paintGL() = 0;

    virtual void resizeGL(int width, int height);

    virtual void enable();
    virtual void disable();

    void setProjectionMode(ProjectionMode projMode);

    static const GLuint loadTexture(const QString & filePath);

    static void drawUnitCube(const QMatrix4x4 & transform);
    static void drawUnitCube(GLuint & list, const QMatrix4x4 & transform);

    static void drawUnitBase();
    static void drawUnitBase(GLuint & list);

public slots:
    void setXRotation(int angle);
    void setYRotation(int angle);
    void setZRotation(int angle);

signals:
    void xRotationChanged(int angle);
    void yRotationChanged(int angle);
    void zRotationChanged(int angle);

protected:
    void applyRotations();
    void setupPerspectiveProjection(float &aspectRatio);
    void setupOrthoProjection(float &aspectRatio);
    virtual void initializeViews();

    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void timerEvent(QTimerEvent * event);
    ThreeDObject* loadModel(const char* path, bool requiresRotation = false);

protected:
    QBasicTimer             *m_timer;
    uint                    m_frame;

    int                     m_xRot;
    int                     m_yRot;
    int                     m_zRot;
    QPoint                  m_lastPos;
    int                     m_width;
    int                     m_height;

    ProjectionMode          m_projMode;
    QMatrix4x4              m_projection;
    QMatrix4x4              m_views[6];
};
