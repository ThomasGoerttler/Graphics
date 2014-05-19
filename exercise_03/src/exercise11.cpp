// ======================================
// 3D Computergrafik
// moodle.hpi3d.de
// ======================================
//
// Sommersemester 2014 - Aufgabenblatt 3
//                     - Aufgabe 11
//
// Diese Datei bearbeiten.
//
// Bearbeiter
// Matr.-Nr: xxxxx
// Matr.-Nr: xxxxx
//
// ======================================

//
// Qt
//
#include <QKeyEvent>
#include <QMatrix4x4>

#include "exercise11.h"
#include "mathmacros.h"

//[-------------------------------------------------------]
//[ Helper functions                                      ]
//[-------------------------------------------------------]

Exercise11::Exercise11(QWidget * parent)
:   AbstractGLExercise(parent), m_cubeList(-1)
{
    // setup view
    m_view = QMatrix4x4();
    m_view.lookAt(
        QVector3D( 0.0f, 3.0f,-6.0f),
        QVector3D( 0.0f, 0.0f, 0.0f),
        QVector3D( 0.0f, 1.0f, 0.0f));

    // setup transform matrix that scales cubes by 0.5
    m_cubeTransform.scale(0.5f);
}

Exercise11::~Exercise11()
{
}

const QString Exercise11::hints() const
{
	return QString("Press [SPACE] to pause or resume animation.");
}

const bool Exercise11::initialize()
{
	return true;
}

void Exercise11::paintGL()
{
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

    // render red unit cube (scaled by m_cubeTransform)
    static const float red[] = {1.0f, 0.0f, 0.0f, 1.0f};
	glMaterialfv(GL_FRONT, GL_DIFFUSE, red);
    drawUnitCube(m_cubeList, m_cubeTransform);

    // setup transformaion for the yellow unit cube
	glPushMatrix();
    rotateClockwise(m_frame);

    // render yellow unit cube (scaled by m_cubeTransform)
	static const float yellow[] = {1.0f, 1.0f, 0.0f, 1.0f};
    glMaterialfv(GL_FRONT, GL_DIFFUSE, yellow);
	drawUnitCube(m_cubeList, m_cubeTransform);

    glPopMatrix();
}

void Exercise11::rotateClockwise(int frame)
{
    /////////////////////////////////////////////////////////////////////////////////////////////////
    // TODO: Aufgabe 11
    // Apply correct transformations (glRotatef, glTranslatef, ..) with respect to the current frame
    /////////////////////////////////////////////////////////////////////////////////////////////////
}

void Exercise11::keyPressEvent(QKeyEvent * keyEvent)
{
    // pause/unpause rendering when space key was pressed
	if (keyEvent->key() & Qt::Key_Space)
	{
		m_active ? disable() : enable();
		keyEvent->accept();
	}
	QGLWidget::keyPressEvent(keyEvent);
}
