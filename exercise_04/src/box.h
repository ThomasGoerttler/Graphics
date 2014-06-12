#ifndef BOX_H
#define BOX_H

#include <QVector3D>

enum GlobalDeformationMode{
    None,
    Pinch,
    Mold,
    Twist,
    Bend
};

class Box
{
public:
    Box(float width, int numCellsXAxis, float height, int numCellsYAxis, float depth, int numCellsZAxis);
    void draw(float animationFrame);

    void setGlobalDeformationMode(GlobalDeformationMode mode);

protected:
    void transformVertex(QVector3D v, float animationFrame);
    void pinch(QVector3D v, float pinchPlateau);
    void mold(QVector3D v, float moldPlateau);
    void twist(QVector3D v, float maxAngle);
    void bend(QVector3D v, float maxAngle);

protected:
    QVector3D               m_overallObjectDimensions;
    QVector3D               m_stepSizes;
    GlobalDeformationMode   m_globalDefMode;
};

#endif // BOX_H
