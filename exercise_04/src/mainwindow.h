
#pragma once

#include <QMainWindow>
#include <QVector>
#include <QSlider>

class AbstractExercise;
class AbstractGLExercise;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget * parent = NULL, Qt::WindowFlags flags = NULL);
	virtual ~MainWindow();

public slots:
    void handleSliderInput(int);

protected:
    void attachExercise(AbstractGLExercise * exercise, const QString & name);
    QSlider *createZoomSlider();
    void setupDockWidget();

protected slots:
    void tabChanged(int index);

protected:
    QStatusBar                  *m_status;
    QTabWidget                  *m_tabs;
    QSlider                     *m_inputSlider;

    float                         m_tickPos;

    QVector<AbstractExercise*>  m_exercises;
};
