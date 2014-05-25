// ======================================
// 3D Computergrafik
// moodle.hpi3d.de
// ======================================
//
// Sommersemester 2014 - Aufgabenblatt 3
//                     - Aufgabe 12
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
#include <QDebug>
#include <QKeyEvent>
#include <QMatrix4x4>

#include "mathmacros.h"

#include "exercise12.h"
#include <iostream>

//[-------------------------------------------------------]
//[ Definitions                                           ]
//[-------------------------------------------------------]
namespace 
{
    const QString TEXTURE_FILENAME = "../data/luxo.png";
}

//[-------------------------------------------------------]
//[ Helper functions                                      ]
//[-------------------------------------------------------]

Exercise12::Exercise12(QWidget * parent)
:   AbstractGLExercise(parent),
    m_textureID(0),
    m_environment(-1)
{
}

Exercise12::~Exercise12()
{
	if (m_textureID != -1)
		glDeleteTextures(1, &m_textureID);

	if (m_quadric)
		gluDeleteQuadric(m_quadric);
}

void Exercise12::drawEnvironment(GLuint & list)
{
    static const GLfloat mat_diffuse_white[] = { 1.f, 1.f, 1.f, 0.f};
    static const GLfloat normal[] = { 0.f, 1.f, 0.f};

    if(list)
        glCallList(list);

    list = glGenLists(1);
    glNewList(list, GL_COMPILE_AND_EXECUTE);

    glPushMatrix();
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_diffuse_white);

	glBegin(GL_QUADS);
        glNormal3fv(normal);
        glVertex3f(-0.9f, 0.8f,-0.1f);
        glVertex3f(-8.0f, 0.8f,-0.1f);
        glVertex3f(-8.0f, 0.8f, 0.1f);
        glVertex3f(-0.9f, 0.8f, 0.1f);
	glEnd();
	glBegin(GL_QUADS);
        glNormal3fv(normal);
        glVertex3f( 0.9f,-1.05f,-0.1f);
        glVertex3f(-0.9f,-1.05f,-0.1f);
        glVertex3f(-0.9f,-1.05f, 0.1f);
        glVertex3f( 0.9f,-1.05f, 0.1f);
	glEnd();
	glBegin(GL_QUADS);
        glNormal3fv(normal);
        glVertex3d( 0.9f, 0.4f, 0.1f);
        glVertex3d( 8.0f, 0.4f, 0.1f);
        glVertex3d( 8.0f, 0.4f,-0.1f);
        glVertex3d( 0.9f, 0.4f,-0.1f);
	glEnd();
    
    QMatrix4x4 transforms[3];

    transforms[0].translate(-4.9f, -1.201f, 0.0f);
    transforms[0].scale(4.f, 2.0f,  4.0f);
    transforms[1].translate(+4.9f, -1.401f, 0.0f);
    transforms[1].scale(4.f, 1.8f, 4.0f);
    transforms[2].translate( 0.0f, -3.0501f, 0.0f);
    transforms[2].scale(1.0f, 2.0f,  4.0f);

    drawUnitCube(transforms[0]);
    drawUnitCube(transforms[1]);
    drawUnitCube(transforms[2]);

    glPopMatrix();

    glEndList();
}

void Exercise12::paintGL()
{
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

    glLoadMatrixf(m_view.data());
    drawEnvironment(m_environment);

    // setup ball material
    static const GLfloat mat_diffuse_white[] = { 1.0f, 1.0f, 1.0f, 0.0f};
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_diffuse_white);

    // setup ball texture
    glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, m_textureID);

    glPushMatrix();	
    // apply translation, scaling and rotation around z axis
    applyBallTransformation(m_frame);
    // apply additional rotation around x axis
    glRotatef(45.0f, 1.0f, 0.0f, 0.0f);
    // render ball
    gluSphere(m_quadric, 0.3f, 32, 32);
    glPopMatrix();

	glDisable(GL_TEXTURE_2D);
}

float deg2rad(float degrees) {
    return degrees * M_PI / 180;
};

void Exercise12::applyBallTransformation(const int frame)
{
    using namespace std;
    
	static const float fX = 0.01f;
    static const int numFramesPerAnimation = static_cast<int>(4.0f / fX);

    static const float r = 0.3f;
    static const float d = 0.3f * r;

    static const float z = 0.0f;
    
    float startX = -2.0;
    float startY = 0.8;
    float endX = 2.0;

    /////////////////////////////////////////////////////////////////////////////////////////////////
    // TODO: Aufgabe 12
    // - Calculate correct translation, scaling and rotation matrices with respect to the current frame
    // - The sphere's environment is defined as follows:
    //              start at    x = -2.0 and y = 0.8
    //              left  cliff x = -0.9
    //              bottom at   y = -1.05;
    //              right cliff x = +0.9 and y = 0.4
    //              end at      x = +2.0
    // - Apply matrices in the correct order, using glMultMatrixf(..)
    /////////////////////////////////////////////////////////////////////////////////////////////////

    int step = frame % numFramesPerAnimation,
        keyStep = floor(step/25),
        keyStepScale = floor(step/5);
    
    
    float heightKeyFrames[] = {
        0.8, 0.8, 0.8, 0.8, 0.8, 0.8, 0.4, -0.4, -1.05, -0.2, 0.22, 0.35, 0.4, 0.4, 0.4, 0.4, 0.4
    };

    float rotateKeyFrames[] = {
        0, 40.0, 80.0, 120.0, 160.0, 200.0, 220.0, 240.0, 260.0, 280.0,
        300.0, 320.0, 360.0, 400.0, 440.0, 480.0, 520.0
    };

    float scaleKeyFrames[81] = {};
    
    for (int i = 0; i < 81; ++i)
        scaleKeyFrames[i] = 1;
    
    scaleKeyFrames[40] = 0.7;
    
    
    float interpolatedYValue = heightKeyFrames[keyStep] +
        (
            (heightKeyFrames[keyStep + 1] - heightKeyFrames[keyStep]) *
            ((step - (keyStep * 25.0))/25.0)
        );

    float interpolatedRotation = -deg2rad(rotateKeyFrames[keyStep] + 
        (
            (rotateKeyFrames[keyStep + 1] - rotateKeyFrames[keyStep]) *
            ((step - (keyStep * 25.0))/25.0)
        ));
    
    float interpolatedScaling = scaleKeyFrames[keyStepScale] + 
        (
            (scaleKeyFrames[keyStepScale + 1] - scaleKeyFrames[keyStepScale]) *
            ((step - (keyStepScale * 5.0))/5.0)
        );
    
    
    const float translate[16] = {
        1,0,0,0,
        0,1,0,0,
        0,0,1,0,
        startX + (fX * step), interpolatedYValue + (0.3 * interpolatedScaling), 0, 1
    };
            
    const float rotate[16] = {
        cos(interpolatedRotation), sin(interpolatedRotation), 0, 0,
        -sin(interpolatedRotation), cos(interpolatedRotation), 0, 0,
        0,0,1,0,
        0,0,0,1
    };
    
    const float scale[16] = {
        1,0,0,0,
        0,interpolatedScaling,0,0,
        0,0,1,0,
        0,0,0,1
    };
    

    //float translate

    
    glMultMatrixf(translate);
    
    glMultMatrixf(scale);
    
    glMultMatrixf(rotate);
    
    //glTranslatef(startX + (fX * step), translate[keySteps] + 0.3, 0);
    
    
}

void Exercise12::initializeGL()
{
	AbstractGLExercise::initializeGL();

    // create texture coordinates for the sphere
	m_quadric = gluNewQuadric();
	
    gluQuadricDrawStyle(m_quadric, GLU_FILL);
	gluQuadricNormals  (m_quadric, GLU_SMOOTH);
	gluQuadricTexture  (m_quadric, GL_TRUE);

	m_textureID = loadTexture(TEXTURE_FILENAME);
}

void Exercise12::keyPressEvent(QKeyEvent * keyEvent)
{
    // pause/unpause rendering when space key was pressed
	if(keyEvent->key() == Qt::Key_Space)
	{
		(m_active) ? disable() : enable();
		keyEvent->accept();
    }
	QGLWidget::keyPressEvent(keyEvent);
}

const bool Exercise12::initialize()
{
    m_view = QMatrix4x4();
    m_view.lookAt(
        QVector3D( 0.4f, 1.2f, 4.0f),
        QVector3D( 0.0f, 0.2f, 0.0f),
        QVector3D( 0.0f, 1.0f, 0.0f));

	return true;
}

const QString Exercise12::hints() const
{
    return QString("Press [SPACE] to pause or resume animation.");
}
