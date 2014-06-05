#include <QKeyEvent>
#include <QMatrix4x4>

#include "exercise16.h"
#include "mathdefinitions.h"
#include "box.h"

Exercise16::Exercise16(float animationFrame, QWidget *parent) : AbstractGLExercise(animationFrame, parent)
{
    m_box = new Box(2.0f, 10, 4.0f, 20, 2.0f, 10);
}

Exercise16::~Exercise16()
{
}

const QString Exercise16::hints() const
{
    return QString("Use [1] to [6] to switch cameras. Use [q],[w],[e],[r],[t] to change global deformation.");
}

const bool Exercise16::initialize()
{

	return true;
}

void Exercise16::paintGL()
{
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

    if(m_projMode == Perspective)
        applyRotations();

    static const float red[] = {1.0f, 0.0f, 0.0f, 1.0f};
    glMaterialfv(GL_FRONT, GL_DIFFUSE, red);

    glPolygonOffset( 1.0, 1.0 );
    glEnable(GL_POLYGON_OFFSET_FILL);
    glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
    m_box->draw(m_animationFrame);
    glDisable(GL_POLYGON_OFFSET_FILL);

    glLineWidth(3.0f);
    glDisable(GL_LIGHTING);
    glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
    m_box->draw(m_animationFrame);

    glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
    glPolygonOffset(0.0,0.0);
    glEnable(GL_LIGHTING);

    glPopMatrix();
}

void Exercise16::keyPressEvent(QKeyEvent * keyEvent)
{
    if(keyEvent->key() > 48 && keyEvent->key() < 55)
    {
        setProjectionMode(ProjectionMode(keyEvent->key() - 49));
        resizeGL(m_width,m_height);
    }
    else switch (keyEvent->key()) {
        case Qt::Key_Q:
            m_box->setGlobalDeformationMode(None);
            break;
        case Qt::Key_W:
            m_box->setGlobalDeformationMode(Pinch);
            break;
        case Qt::Key_E:
            m_box->setGlobalDeformationMode(Mold);
            break;
        case Qt::Key_R:
            m_box->setGlobalDeformationMode(Twist);
            break;
        case Qt::Key_T:
            m_box->setGlobalDeformationMode(Bend);
            break;
        default:
            break;
    }
    QGLWidget::keyPressEvent(keyEvent);
}
