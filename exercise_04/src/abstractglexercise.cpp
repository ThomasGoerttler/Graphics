// ======================================
// 3D Computergrafik
// moodle.hpi3d.de
// ======================================
//
// Sommersemester 2014 - Aufgabenblatt 4
//                     - Aufgabe 14
//
// Diese Datei bearbeiten.
//
// Bearbeiter
// Matr.-Nr: xxxxx
// Matr.-Nr: xxxxx
//
// ======================================

#include "abstractglexercise.h"

#include <cassert>
#include <QBasicTimer>
#include <QTimerEvent>
#include "mathdefinitions.h"
#include "threedobject.h"

namespace
{
    const int MSECS(16);
}

AbstractGLExercise::AbstractGLExercise(float animationFrame, QWidget *parent)
:   AbstractExercise(animationFrame),
    QGLWidget(parent),
    m_timer(new QBasicTimer()),
    m_projMode(Perspective),
    m_width(0),
    m_height(0),
    m_frame(0),
    m_xRot(0),
    m_yRot(0),
    m_zRot(0)
{
    initializeViews();
    m_timer->start(MSECS, this);

    setFocusPolicy(Qt::StrongFocus);
    setFocus();
}

AbstractGLExercise::~AbstractGLExercise()
{
    delete m_timer;
}

void AbstractGLExercise::initializeViews()
{
    /////////////////////////////////////////////////////////////////////////////////////////////////
    // TODO: Aufgabe 14
    // Define different views (via the lookAt()-method) for the orthogonal projection
    /////////////////////////////////////////////////////////////////////////////////////////////////

    m_views[Perspective].lookAt(
        QVector3D( 0.0f, 0.0f, 6.0f),
        QVector3D( 0.0f, 0.0f, 0.0f),
        QVector3D( 0.0f, 1.0f, 0.0f));

//    m_views[OrthoFront].lookAt(..);
//    m_views[OrthoBack].lookAt(..);
//    m_views[OrthoTop].lookAt(..);
//    m_views[OrthoLeft].lookAt(..);
//    m_views[OrthoRight].lookAt(..);
}

void AbstractGLExercise::timerEvent(QTimerEvent * event)
{
    assert(m_timer);

    if(event->timerId() != m_timer->timerId())
        return;

    ++m_frame;
    update();
}

void AbstractGLExercise::setProjectionMode(ProjectionMode projMode)
{
    m_projMode = projMode;
}

void AbstractGLExercise::setXRotation(int angle)
{
    qNormalizeAngle(angle);
    if (angle != m_xRot) {
        m_xRot = angle;
        emit xRotationChanged(angle);
        updateGL();
    }
}

void AbstractGLExercise::setYRotation(int angle)
{
    qNormalizeAngle(angle);
    if (angle != m_yRot) {
        m_yRot = angle;
        emit yRotationChanged(angle);
        updateGL();
    }
}

void AbstractGLExercise::setZRotation(int angle)
{
    qNormalizeAngle(angle);
    if (angle != m_zRot) {
        m_zRot = angle;
        emit zRotationChanged(angle);
        updateGL();
    }
}

void AbstractGLExercise::applyRotations()
{
    glLoadIdentity();

    glTranslatef(0.0, 0.0, -20);

    glRotatef(m_xRot / 16.0, 1.0, 0.0, 0.0);
    glRotatef(m_yRot / 16.0, 0.0, 1.0, 0.0);
    glRotatef(m_zRot / 16.0, 0.0, 0.0, 1.0);

    glEnable(GL_NORMALIZE);
    glScalef(4.0,4.0,4.0);
}

void AbstractGLExercise::setupPerspectiveProjection(float &aspectRatio)
{
    m_projection = QMatrix4x4();
    m_projection.perspective(40.f, aspectRatio, 0.1f, 120.f);
}

void AbstractGLExercise::setupOrthoProjection(float &aspectRatio)
{
    /////////////////////////////////////////////////////////////////////////////////////////////////
    // TODO: Aufgabe 14
    // Setup a correct orthogonal projection via the ortho()-method of QMatrix4x4.
    // Use 0.1 for near and 120.0 for far plane parameters.
    /////////////////////////////////////////////////////////////////////////////////////////////////
    m_projection = QMatrix4x4();
}

void AbstractGLExercise::resizeGL(int width, int height)
{
    m_width = width;
    m_height = height;
    float aspectRatio = float(width)/float(height);

    if(m_projMode == Perspective)
        setupPerspectiveProjection(aspectRatio);
    else
        setupOrthoProjection(aspectRatio);

    glViewport(0, 0, m_width, m_height);

    glMatrixMode(GL_PROJECTION);
    glLoadMatrixf(m_projection.data());

    glMatrixMode(GL_MODELVIEW);
    glLoadMatrixf(m_views[m_projMode].data());

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

void AbstractGLExercise::mousePressEvent(QMouseEvent *event)
{
    m_lastPos = event->pos();
}

void AbstractGLExercise::mouseMoveEvent(QMouseEvent *event)
{
    int dx = event->x() - m_lastPos.x();
    int dy = event->y() - m_lastPos.y();

    if (event->buttons() & Qt::LeftButton) {
        setXRotation(m_xRot + 8 * dy);
        setYRotation(m_yRot + 8 * dx);
    } else if (event->buttons() & Qt::RightButton) {
        setXRotation(m_xRot + 8 * dy);
        setZRotation(m_zRot + 8 * dx);
    }
    m_lastPos = event->pos();
}

ThreeDObject* AbstractGLExercise::loadModel(const char* path, bool requiresRotation)
{
    ThreeDObject* obj = new ThreeDObject(requiresRotation);

    if (!obj->loadOBJ(path))
    {
            printf("***ERROR*** loading obj failed...\n");
            delete obj;
            return nullptr;
     }
    else
    {
        qDebug() << "Object loaded!";
        return obj;
    }
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
