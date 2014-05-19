    
#include "mainwindow.h"
#include "exercise11.h"
#include "exercise12.h"
#include "exercise13.h"

#include <QSettings>
#include <QListWidget>
#include <QTabWidget>
#include <QHBoxLayout>
#include <QScrollArea>
#include <QStatusBar>

const QString settingsGeometry("Geometry");
const QString settingsState("State");
const QString settingsTabsIndex("TabIndex");

MainWindow::MainWindow(QWidget * parent, Qt::WindowFlags flags)
:   QMainWindow(parent, flags)
,   m_status(NULL)
,   m_tabs(NULL)
{
    QSettings::setDefaultFormat(QSettings::IniFormat);
    
    QSettings s;
    restoreGeometry(s.value(settingsGeometry).toByteArray());
    restoreState(s.value(settingsState).toByteArray());

    setWindowTitle("3D Computergrafik I - SS2014 - Blatt 3");
	
    m_status = new QStatusBar();
    setStatusBar(m_status);

    m_tabs = new QTabWidget(this);

    setContentsMargins(4, 4, 4, 4);
    setCentralWidget(m_tabs);

    attachExercise(new Exercise11(), QStringLiteral("Aufgabe 11"));
    attachExercise(new Exercise12(), QStringLiteral("Aufgabe 12"));
    attachExercise(new Exercise13(),QStringLiteral("Aufgabe 13"));

    connect(m_tabs, SIGNAL(currentChanged(int)), this, SLOT(tabChanged(int)));

    const int lastIndex = s.value(settingsTabsIndex, 0).toInt();
    
    if(0 != lastIndex)
        m_tabs->setCurrentIndex(lastIndex);
    else
        tabChanged(0);
}

MainWindow::~MainWindow()
{
    QSettings s;
    s.setValue(settingsGeometry, saveGeometry());
    s.setValue(settingsState, saveState());
    s.setValue(settingsTabsIndex, m_tabs->currentIndex());
}

void MainWindow::tabChanged(int index)
{
    for(int i = 0; i < m_exercises.size(); ++i)
        if(index != i && m_exercises[i]->isActive())
            m_exercises[i]->setActive(false);

    m_exercises[index]->setActive(true);
    m_status->showMessage(m_exercises[index]->hints());
}

void MainWindow::attachExercise(
    AbstractGLExercise * exercise
,   const QString & name)
{
    m_tabs->addTab(exercise, name);
    m_exercises.push_back(exercise);
}
