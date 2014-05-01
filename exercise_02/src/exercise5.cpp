// ======================================
// 3D Computergrafik
// moodle.hpi3d.de
// ======================================
// 
// Sommersemester 2014 - Aufgabenblatt 2
//                     - Aufgabe 5
//
// Diese Datei bearbeiten.
//
// Bearbeiter
// Matr.-Nr: xxxxx
// Matr.-Nr: xxxxx
//
// ======================================

#include "exercise5.h"

//
// Qt
//
#include <QGraphicsView>
#include <QGraphicsPixmapItem>
#include <QGraphicsRectItem>
#include <QMouseEvent>

using namespace Qt;

//[-------------------------------------------------------]
//[ Definitions                                           ]
//[-------------------------------------------------------]
const float threshold = 0.1f;

//[-------------------------------------------------------]
//[ Helper functions                                      ]
//[-------------------------------------------------------]

Exercise5::Exercise5(QWidget *parent) :
    QGraphicsView(parent)
{
    // Create some metaballs
    m_metaballs.push_back(QPoint(10, 10));
    m_metaballs.push_back(QPoint(100, 30));
    m_metaballs.push_back(QPoint(50, 70));
    m_metaballs.push_back(QPoint(80, 40));

    // Set graphics scene
    setScene(&m_scene);

    // Add image item
    QPixmap image;
    m_imageItem = m_scene.addPixmap(image);

    // Render metaballs
    renderMetaballs();
}

Exercise5::~Exercise5()
{
    //
}

/**
*  @brief
*    Called when widget is resized
*/
void Exercise5::resizeEvent(QResizeEvent *event)
{
    // Resize graphics scene according to widget size
    m_scene.setSceneRect(contentsRect());

    // Update metaballs
    renderMetaballs();

    // Call base implementation
    QWidget::resizeEvent(event);
}

/**
*  @brief
*    Called when mouse button is released
*/
void Exercise5::mouseReleaseEvent(QMouseEvent *event)
{
    //////////////////////////////////////////////////
    // TODO: Aufgabe 5
    //////////////////////////////////////////////////

    // Left mouse button
    if (event->button() == Qt::LeftButton) {
        //////////////////////////////////////////////////////////////////////////
        // TODO: Add new metaball
        //////////////////////////////////////////////////////////////////////////
    }

    // Right mouse button
    else if (event->button() == Qt::RightButton) {
        //////////////////////////////////////////////////////////////////////////
        // TODO: remove all metaballs
        //////////////////////////////////////////////////////////////////////////
    }

    // Update metaballs
    renderMetaballs();
}

/**
*  @brief
*    Render metaballs
*/
void Exercise5::renderMetaballs()
{
    //////////////////////////////////////////////////
    // TODO: Aufgabe 5
    //////////////////////////////////////////////////

    // Get image size
    int w = contentsRect().width();
    int h = contentsRect().height();

    // Create temporary map
    float *map = new float[w*h];

    // Draw image
    QPixmap image(w, h);
    QPainter painter(&image);
    for (int y=0; y<h; y++)
    {
        for (int x=0; x<w; x++)
        {
            // Initialize pixel value
            map[y*w+x] = 0.0f;

            // Iterate over list of metaballs
            for (int i=0; i<m_metaballs.size(); i++)
            {
                //////////////////////////////////////////////////////////////////////////
                // TODO: Compute density of metaball i for position (x,y) with a given mass
                //////////////////////////////////////////////////////////////////////////
                float mass = 1000.0f;

                // ...

                //////////////////////////////////////////////////////////////////////////
                // TODO: Add computed density to the current pixel value
                //////////////////////////////////////////////////////////////////////////

                // ...
            }

            //////////////////////////////////////////////////////////////////////////
            // TODO: Scale pixel value to range [0, 1]
            //////////////////////////////////////////////////////////////////////////

            // ...

            // Map value to color
            float c = map[y*w+x];
            if (c >= 0 && c < 0.8f) painter.setPen(QColor((int)((c/0.8f)*255), 0.0, 0.0));
            if (c > 0.8f) painter.setPen(QColor(255, (int)(255*(c-0.8f)/0.2f), (int)(255*(c-0.8f)/0.2f)));

            // Draw pixel
            painter.drawPoint(QPoint(x, y));
        }
    }

    // Update image
    m_imageItem->setPixmap(image);

    // Destroy temporary map
    delete [] map;
}
