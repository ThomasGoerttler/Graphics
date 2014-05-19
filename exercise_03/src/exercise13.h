#pragma once

#include "abstractGLexercise.h"

class PolygonalDrawable;

class Exercise13 : public AbstractGLExercise
{
    Q_OBJECT

public:
    Exercise13(QWidget *parent = NULL);
    virtual ~Exercise13();

    virtual void paintGL() override;

	virtual const QString hints() const;

protected:
	virtual void keyPressEvent(QKeyEvent* keyEvent);

	virtual const bool initialize();

    void interpolateEuler     (const float t);
    void interpolateQuaternion(const float t);
    void interpolateMatrix    (const float t);

    static void slerp(float c[4] /*out*/, const float a[4], const float b[4], const float& t);
	static void lerp(
        float & result,
        const float & a,
        const float & b,
        const float & t);

    static void quat(
        float q[4],
        const float m[16]);

    void axisAngle(
        float & angle,
        float axis[3],
        const float q[4]);

protected:
    void drawEnvironment(
        const float x0,
        const float y0,
        const float x1,
        const float y1);

protected:
    float m_angles0[3];
    float m_angles1[3];

    PolygonalDrawable * m_drawable;
    
    GLuint m_mesh;
    GLuint m_base;
};
