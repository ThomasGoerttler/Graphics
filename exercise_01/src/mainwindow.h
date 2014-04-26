#ifndef __FRAMEWORK_QT_MAINWINDOW_H__
#define __FRAMEWORK_QT_MAINWINDOW_H__


//
// Qt
//
#include <QMainWindow>

class Exercise123;

class MainWindow : public QMainWindow
{
    Q_OBJECT


    //[-------------------------------------------------------]
    //[ Public functions                                      ]
    //[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Constructor
		*
		*  @param parent
		*    Parent widget (can be NULL)
		*  @param flags
		*    QT flags
		*/
        MainWindow(QWidget *parent = NULL, QFlag flags = 0);

		/**
		*  @brief
		*    Destructor
		*/
    	~MainWindow();
  private:
        QWidget* createMultiViewWidget(QList<Exercise123*> &listViews, Exercise123* orig);


};

#endif // __FRAMEWORK_QT_MAINWINDOW_H__