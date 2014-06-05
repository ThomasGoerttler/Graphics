#pragma once

#include "abstractglexercise.h"

class ThreeDObject;

class Exercise15 : public AbstractGLExercise
{
	Q_OBJECT

public:
    Exercise15(float animationFrame = 0.0f, QWidget * parent = NULL);
    virtual ~Exercise15();

    virtual const QString hints() const;

protected:
	virtual const bool initialize();
    virtual void paintGL();

	virtual void keyPressEvent(QKeyEvent * event);

protected:

protected:
    ThreeDObject        *m_threeDObject;
};
