#include "mainwindow.h"
#include "exercise5.h"

//
// Qt
//
#include <QListWidget>
#include <QStackedWidget>
#include <QHBoxLayout>

using namespace Qt;

MainWindow::MainWindow(QWidget *parent, QFlag flags) :
	QMainWindow(parent, flags)
{
    // Set window title
    setWindowTitle("3D Computergrafik I - SS2014 - Aufgabenblatt 2");

    // Create main container
    QWidget *container = new QWidget();
    setCentralWidget(container);

    // Add list (on the left)
    QListWidget *list = new QListWidget(container);
    list->addItem("Aufgabe 5");
    list->setMaximumWidth(150);

    // Add stack of exercise windows (on the right)
    QStackedWidget *stack = new QStackedWidget(container);

    // Add exercise
    Exercise5* e5 = new Exercise5();

    stack->addWidget(e5);

    // Create layout
    QHBoxLayout *layout = new QHBoxLayout;
    layout->addWidget(list);
    layout->addWidget(stack);
    container->setLayout(layout);

    // Connect selection-event of list to select the current visible window
    connect(list, SIGNAL(currentRowChanged(int)), stack, SLOT(setCurrentIndex(int)));
}

MainWindow::~MainWindow()
{
    //
}
