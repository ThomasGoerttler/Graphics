#ifndef __FRAMEWORK_QT_EXERCISE2_H__
#define __FRAMEWORK_QT_EXERCISE2_H__

//
// Qt
//
#include <QGraphicsView>

class Exercise5 : public QGraphicsView {
    
    Q_OBJECT

	public:

        Exercise5(QWidget *parent = NULL);
        ~Exercise5();

    //[-------------------------------------------------------]
    //[ Protected functions                                   ]
    //[-------------------------------------------------------]
	protected:
		/**
		*  @brief
		*    Called when widget is resized
		*
		*  @param event
		*    Resize event
		*/
        virtual void resizeEvent(QResizeEvent *event);

		/**
		*  @brief
		*    Called when mouse button is released
		*
		*  @param event
		*    Mouse event
		*/
        virtual void mouseReleaseEvent(QMouseEvent *event);

		/**
		*  @brief
		*    Render metaballs
		*/
	    void renderMetaballs();

    //[-------------------------------------------------------]
    //[ Protected data                                        ]
    //[-------------------------------------------------------]
	protected:
        QGraphicsScene       m_scene;       /**< Graphics scene */
        QGraphicsPixmapItem* m_imageItem;   /**< Graphics image item */
        QVector<QPoint>      m_metaballs;   /**< List of metaballs */
};


#endif // __FRAMEWORK_QT_EXERCISE2_H__
