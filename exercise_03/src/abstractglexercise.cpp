#include "abstractglexercise.h"

#include <cassert>
#include <QBasicTimer>
#include <QTimerEvent>
#include "mathmacros.h"

namespace
{
    const int MSECS(16);
}

AbstractGLExercise::AbstractGLExercise(QWidget * parent)
:   AbstractExercise(),
    QGLWidget(parent),
    m_timer(new QBasicTimer()),
    m_frame(0)
{
    m_view.lookAt(
        QVector3D( 0.f, 1.f,-6.f),
        QVector3D( 0.f, 0.f, 0.f),
        QVector3D( 0.f, 1.f, 0.f));

    m_timer->start(MSECS, this);

    setFocusPolicy(Qt::StrongFocus);
    setFocus();
}

AbstractGLExercise::~AbstractGLExercise()
{
    delete m_timer;
}

void AbstractGLExercise::timerEvent(QTimerEvent * event)
{
    assert(m_timer);

    if(event->timerId() != m_timer->timerId())
        return;

    ++m_frame;
    update();
}

void AbstractGLExercise::resizeGL(int width, int height)
{
    m_projection = QMatrix4x4();
    m_projection.perspective(40.f, static_cast<float>(width) / static_cast<float>(height), 2.5f, 14.f);

    glViewport(0, 0, width, height);

    glMatrixMode(GL_PROJECTION);
    glLoadMatrixf(m_projection.data());

    glMatrixMode(GL_MODELVIEW);
    glLoadMatrixf(m_view.data());

    updateGL();
}

void AbstractGLExercise::initializeGL()
{
    glClearColor(0.5, 0.5, 0.5, 1.0);
    glShadeModel(GL_SMOOTH);

    glEnable(GL_NORMALIZE);
    glEnable(GL_DEPTH_TEST);

    static const float g_light0[]   = {-2.0f, 8.0f, 8.0f, 1.0f };
    static const float g_ambient0[] = { 0.8f, 0.8f, 1.0f, 1.0f };

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glLightfv(GL_LIGHT0, GL_POSITION, g_light0);
    glLightfv(GL_LIGHT0, GL_AMBIENT, g_ambient0);

    glEnable(GL_CULL_FACE);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
}

void AbstractGLExercise::enable()
{
    m_active = true;
    m_timer->start(MSECS, this);
}

void AbstractGLExercise::disable()
{
    m_active = false;
    m_timer->stop();
}

void AbstractGLExercise::drawUnitCube(
    GLuint & list,
    const QMatrix4x4 & transform)
{
    if(-1 != list)
    {
        glCallList(list);
        return;
    }

    list = glGenLists(1);

    glNewList(list, GL_COMPILE_AND_EXECUTE);
    drawUnitCube(transform);
    glEndList();
}

void AbstractGLExercise::drawUnitCube(const QMatrix4x4 & transform)
{
    glPushMatrix();
    glMultMatrixf(transform.data());

    // PLEASE DO NOT CODE LIKE THIS :D
    // (If you like, try to figure out how this works)

    static const GLshort v[] = { -1,-1,-1,-1,-1, 1,-1, 1,-1,-1, 1, 1, 1,-1,-1, 1,-1, 1, 1, 1,-1, 1, 1, 1 };
    static const GLfloat n[] = { -1, 0, 0, 1, 0, 0, 0,-1, 0, 0, 1, 0, 0, 0,-1, 0, 0, 1 };

    glBegin(GL_QUADS); short j(0);
        for(GLuint64 i(0x166b182acbc); i /= 10ul; glNormal3fv(&n[_int(j / 4) * 3]), glVertex3sv(&v[i % 10ul * 3]), ++j);
        for(GLuint64 i(0x3697e00bbea); i /= 10ul; glNormal3fv(&n[_int(j / 4) * 3]), glVertex3sv(&v[i % 10ul * 3]), ++j);
    glEnd();

    glPopMatrix();
}

void AbstractGLExercise::drawUnitBase(GLuint & list)
{
    if(-1 != list)
    {
        glCallList(list);
        return;
    }

    list = glGenLists(1);

    glNewList(list, GL_COMPILE_AND_EXECUTE);
    drawUnitBase();
    glEndList();
}

void AbstractGLExercise::drawUnitBase()
{
    static const QMatrix4x4 identity;

    static const GLfloat mat_diffuse_x[] = { 1.f, 0.f, 0.f, 0.f};
    static const GLfloat mat_diffuse_y[] = { 0.f, 1.f, 0.f, 0.f};
    static const GLfloat mat_diffuse_z[] = { 0.f, 0.f, 1.f, 0.f};

    static const GLfloat s(0.01f);

    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_diffuse_x);
    glPushMatrix();
    glScalef(0.5f, s, s);
    glTranslatef(1.f, 0.f, 0.f);
    drawUnitCube(identity);
    glPopMatrix();

    glPushMatrix();
    glScalef(s, 0.5f, s);
    glTranslatef(0.f, 1.f, 0.f);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_diffuse_y);
    drawUnitCube(identity);
    glPopMatrix();

    glPushMatrix();
    glScalef(s, s, 0.5f);
    glTranslatef(0.f, 0.f, 1.f);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_diffuse_z);
    drawUnitCube(identity);
    glPopMatrix();
}

const GLuint AbstractGLExercise::loadTexture(const QString & filePath)
{
    const QImage img = QImage(filePath);
    if (img.isNull())
    {
        qCritical("Loading image failed!");
        return -1;
    }

    QImage image = QGLWidget::convertToGLFormat(img);
    GLuint texture(-1);

    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image.width(), image.height(),
        0, GL_RGBA, GL_UNSIGNED_BYTE, image.bits());

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    return texture;
}
