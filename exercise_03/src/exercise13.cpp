// ======================================
// 3D Computergrafik
// moodle.hpi3d.de
// ======================================
//
// Sommersemester 2014 - Aufgabenblatt 3
//                     - Aufgabe 13
//
// Diese Datei bearbeiten.
//
// Bearbeiter
// Matr.-Nr: 766414
// Matr.-Nr: 1337
//
// ======================================

//
// Qt
//
#include <QMatrix4x4>
#include <QKeyEvent>
#include <QRectF>
#include <QSettings>

#include "exercise13.h"
#include "polygonaldrawable.h"
#include "objio.h"
#include "mathmacros.h"

#include <math.h>

//[-------------------------------------------------------]
//[ Definitions                                           ]
//[-------------------------------------------------------]
namespace
{
    const QString settingsGroup("SlerpRotation");
}

//[-------------------------------------------------------]
//[ Helper functions                                      ]
//[-------------------------------------------------------]

Exercise13::Exercise13(QWidget * parent)
:   AbstractGLExercise(parent),
    m_drawable(NULL),
    m_mesh(-1),
    m_base(-1)
{
    // setup angles and view
    m_angles0[0] = 0.0f;
    m_angles0[1] = 0.0f;
    m_angles0[2] = 0.0f;

    m_angles1[0] = 0.0f;
    m_angles1[1] = 0.0f;
    m_angles1[2] = 0.0f;

    m_view = QMatrix4x4();
    m_view.lookAt(
        QVector3D( 0.0f, 2.0f, 10.0f),
        QVector3D( 0.0f, 0.0f,  0.0f),
        QVector3D( 0.0f, 1.0f,  0.0f));
}

Exercise13::~Exercise13()
{
    // clean up, save view settings for later use
    QSettings s;
    s.beginGroup(settingsGroup);

    s.setValue("angle_x", m_angles0[0]);
    s.setValue("angle_y", m_angles0[1]);
    s.setValue("angle_z", m_angles0[2]);

    s.endGroup();

    delete m_drawable;
}

const bool Exercise13::initialize()
{
    if(m_drawable)
        return true;

    // load obj file
    m_drawable = ObjIO::fromObjFile("../data/suzanne.obj");

    //setup view by loading formerly saved view configuration
    QSettings s;
    s.beginGroup(settingsGroup);

    m_angles0[0] = s.value("angle_x", 0.0f).toFloat();
    m_angles0[1] = s.value("angle_y", 0.0f).toFloat();
    m_angles0[2] = s.value("angle_z", 0.0f).toFloat();

    m_angles1[0] = 0.0f;
    m_angles1[1] = 0.0f;
    m_angles1[2] = 0.0f;

    s.endGroup();

    return true;
}

void Exercise13::drawEnvironment(
    const float x0,
    const float y0,
    const float x1,
    const float y1)
{
    const float dy = (y1 - y0) * 0.5;

    glPushMatrix();
    glTranslatef( x0,  y0, 0.f);
    
    for(int i = 0; i < 3; ++i)
    {
        glPushMatrix();
        glRotatef(m_angles0[0], 1.0f, 0.0f, 0.0f);
        glRotatef(m_angles0[1], 0.0f, 1.0f, 0.0f);
        glRotatef(m_angles0[2], 0.0f, 0.0f, 1.0f);
        drawUnitBase();
        glPopMatrix();

        glTranslatef( 0.0f, dy, 0.0f);
    }
    glPopMatrix();

    glPushMatrix();
    glTranslatef( x1,  y0, 0.0f);
    
    for(int i = 0; i < 3; ++i)
    {
        glPushMatrix();
        glRotatef(m_angles1[0], 1.0f, 0.0f, 0.0f);
        glRotatef(m_angles1[1], 0.0f, 1.0f, 0.0f);
        glRotatef(m_angles1[2], 0.0f, 0.0f, 1.0f);
        drawUnitBase();
        glPopMatrix();

        glTranslatef( 0.0f, dy, 0.0f);
    }
    glPopMatrix();
}

void Exercise13::paintGL()
{
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

    glLoadMatrixf(m_view.data());

    static const GLfloat mat_diffuse_white[] = { 1.0f, 1.0f, 1.0f, 0.0f};

    static const float tx[2] = { -4.0f, +4.0f };
    static const float ty[2] = { +2.0f, -2.0f };
    static const float dy    = (ty[1] - ty[0]) * 0.5f;

    drawEnvironment(tx[0], ty[0], tx[1], ty[1]);

    static QMatrix4x4 scale;
    if(scale.isIdentity())
        scale.scale(0.8f);
    
    float t = static_cast<float>(m_frame % 360) / 360.f;
    float x = (tx[1] - tx[0]) * t + tx[0];

    glShadeModel(GL_FLAT);

    for(int i = 0; i < 3; ++i)
    {
        glPushMatrix();

        float y = ty[0] + dy * i;
        glTranslatef( x, y, 0.0f);

        // rotate the model
        switch(i)
        {
            case 0: 
                interpolateMatrix(t);
                break;
            case 1: 
                interpolateEuler(t);
                break;
            case 2: 
                interpolateQuaternion(t);
                break;
            default: 
                break;
        }

        // set the material of the model
        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_diffuse_white);
        m_drawable->draw(m_mesh, scale);

        // render local coordinate system of the model
        glEnable(GL_DEPTH_TEST);
        drawUnitBase(m_base);

        glPopMatrix();
    }
}

void Exercise13::interpolateEuler(const float t)
{
    /////////////////////////////////////////////////////////////////////////////////////////////////
    // TODO: Aufgabe 13
    // - Interpolate rotations by interpolating between the euler angles
    // - hint: use the lerp method (to be defined below)
    // - hint: use glRotatef calls for applying the rotation(s)
    /////////////////////////////////////////////////////////////////////////////////////////////////
	float x,y,z;
	lerp(x, m_angles1[0], m_angles0[0], t);
	lerp(y, m_angles1[1], m_angles0[1], t);
	lerp(z, m_angles1[2], m_angles0[2], t);
	glRotatef(x, 1,0,0);
	glRotatef(y, 0,1,0);
	glRotatef(z, 0,0,1);
    //float x, y, z;
}

void Exercise13::interpolateQuaternion(const float t)
{
    /////////////////////////////////////////////////////////////////////////////////////////////////
    // TODO: Aufgabe 13
    // - Implement a spherical interpolation based on quaternions
    // - hint: use the quat method to convert the matrices to quaternions
    // - hint: use the axisAngle method to get the axis and the angle represented by a quaternion
    // - hint: use the slerp method (to be defined below)
    // - hint: use glRotatef calls for applying the rotation(s)
    /////////////////////////////////////////////////////////////////////////////////////////////////
	float* matrix1 = new float[16];

	glGetFloatv(GL_MODELVIEW_MATRIX, matrix1);
	glRotatef(m_angles0[0], 1, 0, 0);
	glRotatef(m_angles0[1], 0, 1, 0);
	glRotatef(m_angles0[2], 0, 0, 1);

	float* matrix2 = new float[16];
	glGetFloatv(GL_MODELVIEW_MATRIX, matrix2);
	glRotatef(-m_angles0[2], 0, 0, 1);
	glRotatef(-m_angles0[1], 0, 1, 0);
	glRotatef(-m_angles0[0], 1, 0, 0);

	//convert Matrix to Quaternion and interpolate
	float* q1 = new float[4]; quat(q1, matrix1);
	float* q2 = new float[4]; quat(q2, matrix2);
	float* result = new float[4];
	slerp(result, q2, q1, t);

	//convert Quaternion to Axis & Angle und apply Changes
	float angle;
	float* pivot = new float[3];
	axisAngle(angle, pivot, result);
	glRotatef(angle, pivot[0], pivot[1], pivot[2]);
}
    //QMatrix4x4 A, B;


void Exercise13::interpolateMatrix(const float t)
{
    /////////////////////////////////////////////////////////////////////////////////////////////////
    // TODO: Aufgabe 13
    // - Interpolate between the elements of the matrices
    // - hint: use the lerp method (to be defined below)
    // - hint: use glMultMatrix to apply the rotation
    /////////////////////////////////////////////////////////////////////////////////////////////////
	float cosIntrpl, sinIntrpl;
//	float cosIntrpl = t * _cosd(m_angles1[0]) + (1-t) * _cosd(-m_angles0[0]); 
//	float sinIntrpl = t * _sind(m_angles1[0]) + (1-t) * _sind(-m_angles0[0]); 
	lerp(cosIntrpl, _cosd(m_angles1[0]), _cosd(-m_angles0[0]), t);	
	lerp(sinIntrpl, _sind(m_angles1[0]), _sind(-m_angles0[0]), t);
	GLfloat matrixX[16] = {
							1.f, 0.f, 0.f, 0.f,
							0.f, cosIntrpl,	-sinIntrpl,	0.f,
							0.f, sinIntrpl,	cosIntrpl, 0.f,
							0.f, 0.f, 0.f, 1.f	};
	glMultMatrixf(matrixX);

	
	//cosIntrpl = t * _cosd(m_angles1[1]) + (1-t) * _cosd(-m_angles0[1]); 
	//sinIntrpl = t * _sind(m_angles1[1]) + (1-t) * _sind(-m_angles0[1]); 
	lerp(cosIntrpl, _cosd(m_angles1[1]), _cosd(-m_angles0[1]), t);	
	lerp(sinIntrpl, _sind(m_angles1[1]), _sind(-m_angles0[1]), t);
	GLfloat matrixY[16] = {
							cosIntrpl, 0.f,	sinIntrpl, 0.f,
							0.f, 1.f, 0.f, 0.f,
							-sinIntrpl,	0.f, cosIntrpl,	0.f,
							0.f, 0.f, 0.f, 1.f};
	glMultMatrixf(matrixY);
	
//	cosIntrpl = t * _cosd(m_angles1[2]) + (1-t) * _cosd(-m_angles0[2]); 
//	sinIntrpl = t *  _sind(m_angles1[2]) + (1-t) * _sind(-m_angles0[2]); 
	lerp(cosIntrpl, _cosd(m_angles1[2]), _cosd(-m_angles0[2]), t);	
	lerp(sinIntrpl, _sind(m_angles1[2]), _sind(-m_angles0[2]), t);
	GLfloat matrixZ[16] = {
							cosIntrpl, -sinIntrpl, 0.f,	0.f,	
							sinIntrpl, cosIntrpl, 0.f, 0.f, 
							0.f, 0.f, 1.f, 0.f,
							0.f, 0.f, 0.f, 1.f};
	glMultMatrixf(matrixZ);
    //QMatrix4x4 A, B;
    //float C[16];
}

void Exercise13::slerp(
    float result[4],
    const float a[4],
    const float b[4],
    const float & t)
{

	float angle = _acosd( a[0] * b[0] + a[1] * b[1] + a[2] * b[2] + a[3] * b[3]);

	float c1;
	float c2;

	if( angle >= 0.0001) {
		c1 = _sind( (1 - t) * angle) / _sind(angle);
		c2 = _sind(t * angle) / _sind(angle);
	} else {
		c1 = _sind((1-t) * angle) / 0.0001;
		c2 = _sind(t * angle) / 0.0001;
	}
	result[0] = a[0] * c1 + b[0] * c2;
	result[1] = a[1] * c1 + b[1] * c2;
	result[2] = a[2] * c1 + b[2] * c2;
	result[3] = a[3] * c1 + b[3] * c2;
   
}

void Exercise13::lerp(
    float & result,
    const float & a,
    const float & b,
    const float & t)
{
	//result = (b - a) * (1 - t); 
	result = t * a + (1 - t ) * b;
}

void Exercise13::quat(
    float q[4],
    const float m[16])
{   
	double tr = m[0 + 4 * 0] + m[1 + 4 * 1] + m[2 + 4 * 2];
	if (tr > 0.0) 
    {
		q[3] = 0.5 * sqrt(tr + 1.0);
		float s = 0.25 / q[3];
		q[0] = (m[2 + 4 * 1] - m[1 + 4 * 2]) * s;
		q[1] = (m[0 + 4 * 2] - m[2 + 4 * 0]) * s;
		q[2] = (m[1 + 4 * 0] - m[0 + 4 * 1]) * s;
	}
	else 
    {
        int i(0), j, k;

        if (m[1 + 4 * 1] > m[0 + 4 * 0])
            i = 1;
		if (m[2 + 4 * 2] > m[i + 4 * i]) 
            i = 2;
		
        static const int nxt[3] = { 1, 2, 0 };

        j = nxt[i];
		k = nxt[j];
		
        q[i] = 0.5 * sqrt(m[i + 4 * i] - m[j + 4 * j] - m[k + 4 * k] + 1.0);

		float s = 0.25f / q[i];

		q[3] = (m[k + 4 * j] - m[j + 4 * k]) * s;
		q[j] = (m[j + 4 * i] + m[i + 4 * j]) * s;
		q[k] = (m[k + 4 * i] + m[i + 4 * k]) * s;
	}
}

void Exercise13::axisAngle(
    float & angle,
    float axis[3],
    const float q[4])
{
	const double d = q[0] * q[0] + q[1] * q[1] + q[2] * q[2];
	double s = 1.0 / sqrt(d + q[3] * q[3]);

	angle = _deg(2.f * atan2(sqrt(d), static_cast<double>(q[3])));

    axis[0] = q[0] * s;
	axis[1] = q[1] * s;
	axis[2] = q[2] * s;
}

void Exercise13::keyPressEvent(QKeyEvent* keyEvent)
{
    int i = 0;

    switch(keyEvent->key())
    {
        // pause/unpause rendering when space key was pressed
        case Qt::Key_Space:
            isActive() ? disable() : enable();
            break;
        // adjust the start rotation
        case Qt::Key_Z:
            ++i;
        case Qt::Key_Y:
            ++i;
        case Qt::Key_X:
            m_angles0[i] += keyEvent->modifiers() & Qt::SHIFT ? 1.f : -1.f;
            updateGL();
            break;
        // reset the start rotation
        case Qt::Key_R:
            m_angles0[0] = 0.0f;
            m_angles0[1] = 0.0f;
            m_angles0[2] = 0.0f;
            updateGL();
            break;
        default:
            break;
    }

    AbstractGLExercise::keyPressEvent(keyEvent);
}

const QString Exercise13::hints() const
{
	return "Press [SPACE] to pause/resume animation. Use X, Y, and Z keys to modify orientation at start.";
}
