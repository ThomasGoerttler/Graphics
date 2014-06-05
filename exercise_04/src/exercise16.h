#pragma once

#include "abstractglexercise.h"

class Box;

class Exercise16 : public AbstractGLExercise
{
	Q_OBJECT

public:
    Exercise16(float animationFrame = 0.0f, QWidget *parent = NULL);
    virtual ~Exercise16();

    virtual const QString hints() const;

protected:
	virtual const bool initialize();
    virtual void paintGL();

	virtual void keyPressEvent(QKeyEvent * event);

protected:

protected:
    Box     *m_box;
};
