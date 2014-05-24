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
// Matr.-Nr: 768201
// Matr.-Nr: 766414
//
// ======================================

//
// Qt
//
#include <QKeyEvent>
#include <QMatrix4x4>

#include "exercise11.h"
#include "mathmacros.h"
#include <iostream>

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
    using namespace std;
    
    float degree = frame % 720;
    float fraction = degree/90;
    float offset = abs(sin((3 - fraction) * M_PI)) * ((M_SQRT2 - 1)/2);

    if (degree < 90)
        glTranslatef(1 + offset, fraction, 0);
    
    else if (degree < 270)
        glTranslatef(2 - fraction, 1 + offset, 0);
    
    else if (degree < 450)
        glTranslatef(-1 - offset, 4 - fraction, 0);
    
    else  if (degree < 630)
        glTranslatef(fraction - 6, -1 - offset, 0);

    else  if (degree < 720)
        glTranslatef(1 + offset, fraction - 8, 0);
    
    glRotatef(degree, 0, 0, 1);
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
