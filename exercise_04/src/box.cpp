// ======================================
// 3D Computergrafik
// moodle.hpi3d.de
// ======================================
//
// Sommersemester 2014 - Aufgabenblatt 4
//                     - Aufgabe 16
//
// Diese Datei bearbeiten.
//
// Bearbeiter
// Matr.-Nr: xxxxx
// Matr.-Nr: xxxxx
//
// ======================================
#include "box.h"

#include <QtOpenGL>
#define PI 3.14159265

Box::Box(float width, int numCellsXAxis, float height, int numCellsYAxis, float depth, int numCellsZAxis)
{
    m_globalDefMode = None;
    m_overallObjectDimensions = QVector3D(width, height, depth);
    m_stepSizes = QVector3D(
                m_overallObjectDimensions[0]/float(numCellsXAxis),
                m_overallObjectDimensions[1]/float(numCellsYAxis),
                m_overallObjectDimensions[2]/float(numCellsZAxis));
}

void Box::setGlobalDeformationMode(GlobalDeformationMode mode)
{
    m_globalDefMode = mode;
}

void Box::draw(float animationFrame)
{
    glPushMatrix();
    {
        float widthT = m_overallObjectDimensions[0] * 0.5f;
        float heightT = m_overallObjectDimensions[1] * 0.5f;
        float depthT = m_overallObjectDimensions[2] * 0.5f;

        float longestAxis = std::max(heightT,std::max(widthT, depthT));
        glScalef(1.0f/longestAxis, 1.0f/longestAxis, 1.0f/longestAxis);

        glBegin(GL_QUADS);
        {
            glColor3f(0.0f,0.0f,0.0f);
            for(float y=-heightT; y<=heightT-(m_stepSizes[1]*0.5f); y +=m_stepSizes[1])
            {
                for(float x=-widthT; x<=widthT-(m_stepSizes[0]*0.5f); x += m_stepSizes[0])
                {
                    // front
                    glNormal3f(0.0f,0.0f,1.0f);
                    transformVertex(QVector3D(x,y,depthT), animationFrame);
                    transformVertex(QVector3D(x+m_stepSizes[0],y,depthT), animationFrame);
                    transformVertex(QVector3D(x+m_stepSizes[0],y+m_stepSizes[1],depthT), animationFrame);
                    transformVertex(QVector3D(x,y+m_stepSizes[1],depthT), animationFrame);

                    // back
                    glNormal3f(0.0f,0.0f,-1.0f);
                    transformVertex(QVector3D(x,y+m_stepSizes[1],-depthT), animationFrame);
                    transformVertex(QVector3D(x+m_stepSizes[0],y+m_stepSizes[1],-depthT), animationFrame);
                    transformVertex(QVector3D(x+m_stepSizes[0],y,-depthT), animationFrame);
                    transformVertex(QVector3D(x,y,-depthT), animationFrame);
                }
            }

            for(float x=-widthT; x<=widthT-(m_stepSizes[0]*0.5f); x +=m_stepSizes[0])
            {
                for(float z=-depthT; z<=depthT-(m_stepSizes[2]*0.5f); z += m_stepSizes[2])
                {
                    // top
                    glNormal3f(0.0f,1.0f,0.0f);
                    transformVertex(QVector3D(x,heightT,z+m_stepSizes[2]), animationFrame);
                    transformVertex(QVector3D(x+m_stepSizes[0],heightT,z+m_stepSizes[2]), animationFrame);
                    transformVertex(QVector3D(x+m_stepSizes[0],heightT,z), animationFrame);
                    transformVertex(QVector3D(x,heightT,z), animationFrame);

                    // bottom
                    glNormal3f(0.0f,-1.0f,0.0f);
                    transformVertex(QVector3D(x,-heightT,z), animationFrame);
                    transformVertex(QVector3D(x+m_stepSizes[0],-heightT,z), animationFrame);
                    transformVertex(QVector3D(x+m_stepSizes[0],-heightT,z+m_stepSizes[2]), animationFrame);
                    transformVertex(QVector3D(x,-heightT,z+m_stepSizes[2]), animationFrame);
                }
            }

            for(float z=-depthT; z<=depthT-(m_stepSizes[2]*0.5f); z +=m_stepSizes[2])
            {
                for(float y=-heightT; y<=heightT-(m_stepSizes[1]*0.5f); y += m_stepSizes[1])
                {
                    // left
                    glNormal3f(-1.0f,0.0f,0.0f);
                    transformVertex(QVector3D(-widthT,y,z), animationFrame);
                    transformVertex(QVector3D(-widthT,y,z+m_stepSizes[2]), animationFrame);
                    transformVertex(QVector3D(-widthT,y+m_stepSizes[1],z+m_stepSizes[2]), animationFrame);
                    transformVertex(QVector3D(-widthT,y+m_stepSizes[1],z), animationFrame);

                    // right
                    glNormal3f(1.0f,0.0f,0.0f);
                    transformVertex(QVector3D(widthT,y+m_stepSizes[1],z), animationFrame);
                    transformVertex(QVector3D(widthT,y+m_stepSizes[1],z+m_stepSizes[2]), animationFrame);
                    transformVertex(QVector3D(widthT,y,z+m_stepSizes[2]), animationFrame);
                    transformVertex(QVector3D(widthT,y,z), animationFrame);
                }
            }
        }
        glEnd();
    }
    glPopMatrix();
}

void Box::transformVertex(QVector3D v, float animationFrame)
{
    switch (m_globalDefMode)
    {
        case Pinch:
            pinch(v, 1.0f - animationFrame);
            break;
        case Mold:
            mold(v, 1.0f - animationFrame);
            break;
        case Twist:
            twist(v, animationFrame*360.0f);
            break;
        case Bend:
            bend(v, animationFrame*90.0f);
            break;
        default:
            glVertex3fv(&v[0]);
    }
}

void Box::pinch(QVector3D v, float pinchPlateau)
{
    /////////////////////////////////////////////////////////////////////////////////////////////////
    // TODO: Aufgabe 16
    // Apply a pinch deformation to the given vertex v.
    // Take into account the pinchPlateau parameter
    //      0.0f: No deformation at all
    //      1.0f: Maximum deformation
    // Tip: Use m_overallObjectDimensions to get the extents of the x, y and z dimension
    // Tip: Keep in mind that the box is located in the coordinate system origin
    /////////////////////////////////////////////////////////////////////////////////////////////////

    glVertex3fv(&v[0]);
}

void Box::mold(QVector3D v, float moldPlateau)
{
    /////////////////////////////////////////////////////////////////////////////////////////////////
    // TODO: Aufgabe 16
    // Apply a mold deformation to the given vertex v.
    // Take into account the moldPlateau parameter
    //      0.0f: No deformation at all
    //      1.0f: Maximum deformation
    // Tip: Use m_overallObjectDimensions to get the extents of the x, y and z dimension
    // Tip: Keep in mind that the box is located in the coordinate system origin
    /////////////////////////////////////////////////////////////////////////////////////////////////

    glVertex3fv(&v[0]);
}

void Box::twist(QVector3D v, float maxAngle)
{
    /////////////////////////////////////////////////////////////////////////////////////////////////
    // TODO: Aufgabe 16
    // Apply a twist deformation to the given vertex v.
    // Take into account the maxAngle parameter, that defines the maximum rotation angle
    // Tip: Use m_overallObjectDimensions to get the extents of the x, y and z dimension
    // Tip: Keep in mind that the box is located in the coordinate system origin
    /////////////////////////////////////////////////////////////////////////////////////////////////

    glVertex3fv(&v[0]);
}

void Box::bend(QVector3D v, float maxAngle)
{
    /////////////////////////////////////////////////////////////////////////////////////////////////
    // TODO: Aufgabe 16
    // Apply a bend deformation to the given vertex v.
    // Take into account the maxAngle parameter, that defines the maximum rotation angle
    // Tip: Use m_overallObjectDimensions to get the extents of the x, y and z dimension
    // Tip: Keep in mind that the box is located in the coordinate system origin
    /////////////////////////////////////////////////////////////////////////////////////////////////

    glVertex3fv(&v[0]);
}
