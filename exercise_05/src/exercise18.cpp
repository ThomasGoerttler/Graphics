
#include "exercise18.h"

#include <QKeyEvent>

#include "polygonaldrawable.h"
#include "halfedgestructure.h"
#include "vertexreuse.h"
#include "objio.h"

namespace
{
    const QString SETTINGS_GROUP("NormalsThreshold");
}


Exercise18::Exercise18(QWidget  * parent)
:   AbstractGLExercise(parent)
,   m_drawable(NULL)
,   m_he(NULL)
,   m_threshold(0.f)
,   m_normals(true)
{
    m_view = QMatrix4x4();
    m_view.lookAt(
        QVector3D( 0.f, 1.f,  4.f)
    ,   QVector3D( 0.f, 0.f,  0.f)
    ,   QVector3D( 0.f, 1.f,  0.f));
}

Exercise18::~Exercise18()
{
    QSettings s;
    s.beginGroup(SETTINGS_GROUP);

    s.setValue("threshold", m_threshold);
    s.setValue("normals", m_normals);

    s.endGroup();


    delete m_drawable;
    delete m_he;
}

const bool Exercise18::initialize()
{
    if(m_drawable)
        return true;

    QSettings s;
    s.beginGroup(SETTINGS_GROUP);

    m_threshold = s.value("threshold", 0.f).toFloat();
    m_normals = s.value("normals", true).toBool();

    s.endGroup();


    m_drawable = ObjIO::fromObjFile("../data/suzanne.obj");
    
    VertexReuse::optimize(
        m_drawable->vertices()
    ,   m_drawable->normals()
    ,   m_drawable->texcs()
    ,   m_drawable->indices());

    m_he = new HalfEdgeStructure(*m_drawable);
    m_he->calculatePerVertexNormals(m_threshold);

    return true;
}


void Exercise18::paintGL()
{
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

    glLoadMatrixf(m_view.data());
    
    glPushMatrix();

    glRotatef(static_cast<float>(m_frame % (4 * 360)) * 0.25f, 0.f, 1.f, 0.f);    
    glScalef(1.f, 1.f, 1.f);

    draw();

    glPopMatrix();
}

void Exercise18::draw()
{
	glShadeModel(GL_SMOOTH);
	glPushMatrix();

    static const GLfloat mat_diffuse_white[] = { 1.f, 1.f, 1.f, 0.f};
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_diffuse_white);

    glEnable(GL_CULL_FACE);
    glBegin(GL_TRIANGLES);

    glColor3f(1.f, 1.f, 1.f);

    HalfEdgeStructure::t_faces::const_iterator i = m_he->faces().begin();
    const HalfEdgeStructure::t_faces::const_iterator iEnd = m_he->faces().end();
    for(; i != iEnd; ++i)
    {
        const HalfEdgeStructure::HalfEdge * const he0 = i->he->prev;
        const HalfEdgeStructure::HalfEdge * const he1 = i->he;
        const HalfEdgeStructure::HalfEdge * const he2 = i->he->next;

        //glNormal3f(i->normal.x(), i->normal.y(), i->normal.z());

        glNormal3f(he0->normal.x(), he0->normal.y(), he0->normal.z());
        glVertex3f(he0->vertex->x(), he0->vertex->y(), he0->vertex->z());
        glNormal3f(he1->normal.x(), he1->normal.y(), he1->normal.z());
        glVertex3f(he1->vertex->x(), he1->vertex->y(), he1->vertex->z());
        glNormal3f(he2->normal.x(), he2->normal.y(), he2->normal.z());
        glVertex3f(he2->vertex->x(), he2->vertex->y(), he2->vertex->z());
    }
    glEnd();

    if(m_normals)
    {
        drawFaceNormals();
        drawVertexNormals();
    }

	glPopMatrix();
}

const QString Exercise18::hints() const
{
	return "Toggle normals with [n]. Use [+] and [-] to adjust angle threshold. Press [Space] for toggle rotation.";
}

void Exercise18::keyPressEvent(QKeyEvent* keyEvent)
{
    const int key = keyEvent->key();
    
    if(key == Qt::Key_Plus || key == Qt::Key_Minus)
    {
        m_threshold += key == Qt::Key_Plus ? 1 : -1;
        m_threshold = qBound<float>(0.f, m_threshold, 180.f);

        m_he->calculatePerVertexNormals(m_threshold);
        updateGL();

        keyEvent->accept();
    }

    switch(key)
    {
    case Qt::Key_Space:
        isActive() ? disable() : enable();
        break;
    case Qt::Key_N:
        m_normals = !m_normals;
        updateGL();
        break;
    default:
        break;
    }

	AbstractGLExercise::keyPressEvent(keyEvent);
}

void Exercise18::drawFaceNormals()
{
    if(!m_he)
        return;

	glDisable(GL_LIGHTING);
	glBegin(GL_LINES);

    glColor3f(1.0f, 0.0f, 1.0f);

    HalfEdgeStructure::t_faces::const_iterator i = m_he->faces().begin();
    const HalfEdgeStructure::t_faces::const_iterator iEnd = m_he->faces().end();
    for(; i != iEnd; ++i)
    {
		QVector3D middleVector = (*(i->he->vertex) + *(i->he->next->vertex) + *(i->he->prev->vertex))/3.0;
		glVertex3f(middleVector.x(), middleVector.y(), middleVector.z());
		glVertex3f(middleVector.x() + i->normal.y() * 0.1, middleVector.y() + i->normal.y() * 0.1, middleVector.z() + i->normal.z() * 0.1);
    }

    glEnd();
    glEnable(GL_LIGHTING);
}

void Exercise18::drawVertexNormals()
{
    if(!m_he)
        return;

	glDisable(GL_LIGHTING);
	glBegin(GL_LINES);

    glColor3f(0.f, 1.f, 0.f);

    HalfEdgeStructure::t_halfEdges::const_iterator i = m_he->halfEdges().begin();
    const HalfEdgeStructure::t_halfEdges::const_iterator iEnd = m_he->halfEdges().end();
    for(; i != iEnd; ++i)
    {
		QVector3D v = i->vertex[0];
		QVector3D n = i->normal * 0.1;
		glVertex3f(v.x(), v.y(), v.z());
		v += n ;
		glVertex3f(v.x(), v.y(), v.z());
    }

    glEnd();
    glEnable(GL_LIGHTING);
}
