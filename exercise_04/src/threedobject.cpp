// ======================================
// 3D Computergrafik
// moodle.hpi3d.de
// ======================================
//
// Sommersemester 2014 - Aufgabenblatt 4
//                     - Aufgabe 15 + Aufgabe 17
//
// Diese Datei bearbeiten.
//
// Bearbeiter
// Matr.-Nr: 768201
// Matr.-Nr: 766414
//
// ======================================

#include "threedobject.h"

#include <QtOpenGL>

#include <algorithm>
#include <cfloat>
#include <iostream>


ThreeDObject::ThreeDObject( bool requiresInnerRotation) :
    m_requiresInnerRotation(requiresInnerRotation),
    m_llf(FLT_MAX, FLT_MAX, FLT_MAX),
    m_urb(-FLT_MAX, -FLT_MAX, -FLT_MAX)
{
}

bool ThreeDObject::loadOBJ(const char *path)
{
    // http://en.wikipedia.org/wiki/Wavefront_.obj_file
    // http://en.wikibooks.org/wiki/OpenGL_Programming/Modern_OpenGL_Tutorial_Load_OBJ
    const char *s_sep = " \t\n\r";

    FILE *f = fopen(path, "rt");
    if (!f)
        return false;

    bool result = true;
    char buf[256];
    while (result && !feof(f)) {
        strcpy(buf, "");
        fgets(buf, 256, f);

        char *token = strtok( buf, s_sep);
        if (token) {
            switch (token[0]) {
                case 'v': {
                    if ((token[1] == 0) || (token[1] == 'n') || (token[1] == 't')) {
                        char type = token[1];

                        token = strtok( NULL, s_sep);
                        int i = 0;
                        int r = 3;
                        if(type == 't') r = 2;
                        float v[3];
                        while (token && (i < r)) {
                            v[i] = atof(token);
                            token = strtok( NULL, s_sep);
                            ++i;
                        }

                        if ((i != r) ){//|| token) {
                            result = false;
                            break;
                        }

                        switch(type)
                        {
                        case 0:
                            {
                                QVector3D vert(v[0],v[1],v[2]);
                                m_vertices.push_back(vert);
                                break;
                            }
                        case 'n':
                            {
                                QVector3D normal(v[0],v[1],v[2]);
                                m_normals.push_back(normal);
                                break;
                            }
                        default: break;
                        }

                    }
                    break;
                }

                case 'f': {
                    face f;
                    for (int i = 0; i < 3; ++i) {
                        token = strtok( NULL, s_sep);
                        if (!token) {
                            result = false;
                            break;
                        }

                        char *p = strchr(token, '/');
                        char *q = strrchr(token, '/');
                        if (!p || !q) {
                            result = false;
                            break;
                        }

                        *p = 0;
                        ++q;

                        f.vertexIndices[i] = atoi(token) - 1;
                        f.normalIndices[i] = atoi(q) - 1;
                    }
                    if (result) {
                        m_faces.push_back(f);
                    }
                    break;
                }
            }
        }
    }

    fclose(f);

    // adjust signs of normals/vertices and calculate bounding box
    for (unsigned j = 0; j < m_faces.size(); ++j)
    {
        for (unsigned i = 0; i < 3; ++i)
        {
            int n = m_faces[j].normalIndices[i];
            int v = m_faces[j].vertexIndices[i];
            m_faces[j].center += m_vertices[v];
            m_faces[j].avgNormal += m_normals[n];
            if(n < 0)
            {
                m_normals[-n][0] = -m_normals[-n][0];
                m_normals[-n][1] = -m_normals[-n][1];
                m_normals[-n][2] = -m_normals[-n][2];
                m_faces[j].normalIndices[i] = -n;
            }
            if(v < 0)
            {
                m_vertices[-v][0] = -m_vertices[-v][0];
                m_vertices[-v][1] = -m_vertices[-v][1];
                m_vertices[-v][2] = -m_vertices[-v][2];
                m_faces[j].vertexIndices[i] = -v;
            }

            for(int dim = 0; dim < 3; dim++)
            {
                if(m_llf[dim] > m_vertices[v][dim])
                    m_llf[dim] = m_vertices[v][dim];

                if(m_urb[dim] < m_vertices[v][dim])
                    m_urb[dim] = m_vertices[v][dim];
            }
        }
        m_faces[j].center /= 3.0f;
        m_faces[j].avgNormal /= 3.0f;
    }
    m_longestExtent =  std::max(m_urb[0]-m_llf[0],std::max(m_urb[1]-m_llf[1], m_urb[2]-m_llf[2]));

    return result;
}

void ThreeDObject::drawHaloedLines(float animationFrame)
{
     
     QVector3D v;
     
     glEnable(GL_COLOR_MATERIAL);

	glLineWidth(16.0f * animationFrame);
	glDepthFunc(GL_ALWAYS);
	glColorMask(GL_FALSE,GL_FALSE,GL_FALSE,GL_FALSE);
	glBegin(GL_LINES); 
	{
		for (unsigned j = 0; j < m_faces.size(); ++j) {
            for (unsigned i = 0; i < 3; ++i)
            {
                glNormal3fv(&m_normals[m_faces[j].normalIndices[i]][0]);
                v = m_vertices[m_faces[j].vertexIndices[i]];
                glVertex3fv(&v[0]);
            }
		}
	}
	glEnd();

	glLineWidth(2.0f);
	glDepthFunc(GL_LEQUAL);
	glColorMask(GL_TRUE,GL_TRUE,GL_TRUE,GL_TRUE);
	glBegin(GL_LINES);
	{
		for (unsigned j = 0; j < m_faces.size(); ++j) {
            for (unsigned i = 0; i < 3; ++i)
            {
                glNormal3fv(&m_normals[m_faces[j].normalIndices[i]][0]);
                v = m_vertices[m_faces[j].vertexIndices[i]];
                glVertex3fv(&v[0]);
            }
		}
	}
	glEnd();
}

void ThreeDObject::draw(float animationFrame)
{
    glPushMatrix();

    float scaleFactor = 3.0f;

    if(m_requiresInnerRotation)
    {
        // Beware: Translation is applied first (matrices read in column major order by opengl)!
        glTranslatef(0.0f, -0.5f, -0.5f);
        glRotatef(-90, 1.0f, 0.0f, 0.0f);
        glScalef(scaleFactor/m_longestExtent, scaleFactor/m_longestExtent, scaleFactor/m_longestExtent);
        glTranslatef(-(m_llf[0]+m_urb[0])*0.5f, -(m_llf[2]+m_urb[2])*0.5f, -(m_llf[1]+m_urb[1])*0.5f);
    }
    else
    {
        // Beware: Translation is applied first (matrices read in column major order by opengl)!
        glScalef(scaleFactor/m_longestExtent, scaleFactor/m_longestExtent, scaleFactor/m_longestExtent);
        glTranslatef(-(m_llf[0]+m_urb[0])*0.5f, -(m_llf[1]+m_urb[1])*0.5f, -(m_llf[2]+m_urb[2])*0.5f);
    }

    drawFace(animationFrame);

    glPopMatrix();
}

void ThreeDObject::drawFace(float &animationFrame)
{
    glBegin(GL_TRIANGLES);
    {
        for (unsigned j = 0; j < m_faces.size(); ++j) {

            QVector3D center(
                    m_faces[j].center[0],
                    m_faces[j].center[1],
                    m_faces[j].center[2]
                ),
                vec;

            QMatrix4x4 rotMatrix;
            rotMatrix.rotate(animationFrame * 360, 0.0, 1.0, 0.0);


            for (unsigned i = 0; i < 3; ++i) {

                glNormal3fv(&m_normals[m_faces[j].normalIndices[i]][0]);

                vec = m_vertices[m_faces[j].vertexIndices[i]];

                // Move away from center of car
                vec += (m_faces[j].avgNormal * animationFrame);

                // Rotate around center of face
                vec -= center;
                vec = vec * rotMatrix;
                vec += center;
                
                glVertex3fv(&vec[0]);
            }
        }
    }
    glEnd();
}
