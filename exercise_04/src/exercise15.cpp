#include <QKeyEvent>
#include <QMatrix4x4>

#include "exercise15.h"
#include "mathdefinitions.h"
#include "threedobject.h"

Exercise15::Exercise15(float animationFrame, QWidget *parent) : AbstractGLExercise(animationFrame, parent)
{
    m_threeDObject = loadModel("../data/challenger.obj", true);
}

Exercise15::~Exercise15()
{
}

const QString Exercise15::hints() const
{
    return QString("Use [1] to [6] to switch cameras (1: perspective, 2-6: orthogonal).");
}

const bool Exercise15::initialize()
{
	return true;
}

void Exercise15::paintGL()
{
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

    if(m_projMode == Perspective)
        applyRotations();

    static const float red[] = {1.0f, 0.0f, 0.0f, 1.0f};
    glMaterialfv(GL_FRONT, GL_DIFFUSE, red);
    m_threeDObject->draw(m_animationFrame);

    glPopMatrix();
}

void Exercise15::keyPressEvent(QKeyEvent * keyEvent)
{
    if(keyEvent->key() > 48 && keyEvent->key() < 55)
    {
        setProjectionMode(ProjectionMode(keyEvent->key() - 49));
        resizeGL(m_width,m_height);
    }
    QGLWidget::keyPressEvent(keyEvent);
}
