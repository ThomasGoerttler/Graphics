#ifndef OBJREADER_H
#define OBJREADER_H

#include <QVector2D>
#include <QVector3D>

#include <cassert>
#include <cstdio>
#include <cmath>
#include <vector>
#include <string>

struct face {
    QVector3D vertexIndices;
    QVector3D normalIndices;
    QVector3D avgNormal;
    QVector3D center;
};

class ThreeDObject
{
public:
    ThreeDObject(bool requiresInnerRotation = false);
    bool loadOBJ(const char *path);
    void draw(float animationFrame = 0.0f);
    void drawHaloedLines(float animationFrame);

protected:
    void drawFace(float &animationFrame);
    void applyInnerRotation();

protected:
    std::vector<QVector3D>  m_vertices;
    std::vector<QVector3D>  m_normals;
    std::vector<face>       m_faces;
    QVector3D               m_llf;
    QVector3D               m_urb;
    float                   m_longestExtent;

    bool                    m_requiresInnerRotation;
};

#endif // OBJREADER_H
