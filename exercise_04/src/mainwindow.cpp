    
#include "mainwindow.h"
#include "exercise15.h"
#include "exercise16.h"
#include "exercise17.h"

#include <QSettings>
#include <QListWidget>
#include <QTabWidget>
#include <QHBoxLayout>
#include <QScrollArea>
#include <QStatusBar>

const QString settingsGeometry("Geometry");
const QString settingsState("State");
const QString settingsTabsIndex("TabIndex");
const QString settingsSlider("SliderPos");

MainWindow::MainWindow(QWidget * parent, Qt::WindowFlags flags)
:   QMainWindow(parent, flags),
    m_status(NULL),
    m_tabs(NULL)
{
    QSettings::setDefaultFormat(QSettings::IniFormat);
    
    QSettings s;
    restoreGeometry(s.value(settingsGeometry).toByteArray());
    restoreState(s.value(settingsState).toByteArray());
    m_tickPos = s.value(settingsSlider, 0).toFloat();

    setWindowTitle("3D Computergrafik I - SS2014 - Blatt 4");
	
    m_status = new QStatusBar();
    setStatusBar(m_status);

    m_tabs = new QTabWidget(this);

    setContentsMargins(4, 4, 4, 4);
    setCentralWidget(m_tabs);
    setupDockWidget();

    attachExercise(new Exercise15(m_tickPos), QStringLiteral("Aufgabe 15"));
    attachExercise(new Exercise16(m_tickPos), QStringLiteral("Aufgabe 16"));
    attachExercise(new Exercise17(m_tickPos), QStringLiteral("Aufgabe 17"));

    connect(m_tabs, SIGNAL(currentChanged(int)), this, SLOT(tabChanged(int)));
    connect(m_inputSlider, SIGNAL(valueChanged(int)), this, SLOT(handleSliderInput(int)));

    const int lastIndex = s.value(settingsTabsIndex, 0).toInt();

    if(0 != lastIndex)
        m_tabs->setCurrentIndex(lastIndex);
    else
    {
        tabChanged(0);
    }
}

MainWindow::~MainWindow()
{
    QSettings s;
    s.setValue(settingsGeometry, saveGeometry());
    s.setValue(settingsState, saveState());
    s.setValue(settingsTabsIndex, m_tabs->currentIndex());
    s.setValue(settingsSlider, m_tickPos);
}

void MainWindow::setupDockWidget()
{
    m_inputSlider = createZoomSlider();

    QDockWidget *dock = new QDockWidget(this);
    dock->setFeatures(QDockWidget::DockWidgetMovable | QDockWidget::DockWidgetFloatable);
    dock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    addDockWidget(Qt::LeftDockWidgetArea, dock);

    QFrame *contentFrame= new QFrame();
    dock->setWidget(contentFrame);
    QVBoxLayout *dockLayout = new QVBoxLayout;
    dockLayout->addWidget(m_inputSlider);
    contentFrame->setLayout(dockLayout);
}

QSlider *MainWindow::createZoomSlider()
{
    QSlider *slider = new QSlider(Qt::Vertical);
    slider->setRange(0, 100);
    slider->setSingleStep(1);
    slider->setTickInterval(10);
    slider->setTickPosition(QSlider::TicksRight);
    slider->setValue(m_tickPos*float(slider->maximum()));
    return slider;
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
    AbstractGLExercise * exercise,
    const QString & name)
{
    m_tabs->addTab(exercise, name);
    m_exercises.push_back(exercise);
}

void MainWindow::handleSliderInput(int value)
{
    m_tickPos = float(value)/float(m_inputSlider->maximum());
    for(AbstractExercise *ex : m_exercises)
    {
        ex->setAnimationFrame(m_tickPos);
    }
}
