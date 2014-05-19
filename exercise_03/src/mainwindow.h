
#pragma once

#include <QMainWindow>
#include <QVector>

class AbstractExercise;
class AbstractGLExercise;


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
	MainWindow(
		QWidget * parent = NULL
    ,   Qt::WindowFlags flags = NULL);

	virtual ~MainWindow();

protected:
    void attachExercise(
        AbstractGLExercise * exercise
    ,   const QString & name);

protected slots:
    void tabChanged(int index);

protected:
    QStatusBar * m_status;
    QTabWidget * m_tabs;

    QVector<AbstractExercise*> m_exercises;
};