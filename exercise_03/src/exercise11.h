#pragma once

#include "abstractglexercise.h"


class Exercise11 : public AbstractGLExercise
{
	Q_OBJECT

public:
    Exercise11(QWidget * parent = NULL);
    virtual ~Exercise11();

	virtual const QString hints() const;

protected:
	virtual const bool initialize();
    virtual void paintGL();

	virtual void keyPressEvent(QKeyEvent * event);

protected:
	void rotateClockwise(int frame);

protected:
    GLuint      m_cubeList;
    QMatrix4x4  m_cubeTransform;
};
