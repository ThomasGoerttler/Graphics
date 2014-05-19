#pragma once

#include "abstractglexercise.h"

class Exercise12 : public AbstractGLExercise
{
	Q_OBJECT

public:
    Exercise12(QWidget * parent = NULL);
    virtual ~Exercise12();

	virtual const QString hints() const;

protected:
	virtual const bool initialize();

	virtual void keyPressEvent(QKeyEvent * event);

	virtual void paintGL();
	virtual void initializeGL();
	
    static void drawEnvironment(GLuint & list);

    virtual void applyBallTransformation(const int frame);

protected:
	GLuint m_textureID;
	GLUquadricObj * m_quadric;

    GLuint m_environment;
};
