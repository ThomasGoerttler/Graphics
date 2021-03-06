
#include "mainwindow.h"

#include <iostream>
#include <ctime>

#include <QApplication>


int main(int argc, char* argv[])
{
    int result = -1;

    srand(time(NULL));

    QApplication::setOrganizationName("Hasso-Plattner-Institut CGS");
    QApplication::setApplicationName("CG1 Blatt 3");

	QApplication * app = new QApplication(argc, argv);

    MainWindow * mw = new MainWindow();
    mw->resize(700, 300);
    mw->show();

	result = app->exec();

	// Clean Up

	delete mw;
	delete app;

    return result;
}
