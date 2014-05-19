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
// Matr.-Nr: 768201
// Matr.-Nr: 766414
//
// ======================================

#include "exercise5.h"
#include <math.h>
#include <iostream>

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
const float densitySumThreshold = 5.0f;

//[-------------------------------------------------------]
//[ Helper functions                                      ]
//[-------------------------------------------------------]

Exercise5::Exercise5(QWidget *parent) : QGraphicsView(parent) {
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

Exercise5::~Exercise5() {
    //
}

/**
*  @brief
*    Called when widget is resized
*/
void Exercise5::resizeEvent (QResizeEvent *event) {
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
void Exercise5::mouseReleaseEvent (QMouseEvent *event) {
    
    // Left mouse button
    if (event->button() == Qt::LeftButton) {
        
        m_metaballs.push_back(QPoint(event->x(), event->y()));
    }

    // Right mouse button
    else if (event->button() == Qt::RightButton) {
        
        m_metaballs.clear();
    }

    // Update metaballs
    renderMetaballs();
}

/**
*  @brief
*    Render metaballs
*/
void Exercise5::renderMetaballs () {
        
    // Get image size
    int w = contentsRect().width();
    int h = contentsRect().height();

    // Create temporary map
    float *map = new float[w*h];
    float max = 0.0;
    float colorThreshold = 0.8;

    // Draw image
    QPixmap image(w, h);
    QPainter painter(&image);
    
    for (int y = 0; y < h; y++) {
        for (int x = 0; x < w; x++) {
            
            int pixelNumber = y * w + x;
            
            // Initialize pixel value
            map[pixelNumber] = 0.0f;

            // Iterate over list of metaballs
            for (int i = 0; i < m_metaballs.size(); i++) {        
               
                float mass = 1000.0f;
                
                float density = mass /
                    (pow(x - m_metaballs[i].x(), 2) +
                    pow(y - m_metaballs[i].y(), 2));
                
                map[pixelNumber] += density;
            }
            
            if(map[pixelNumber] > densitySumThreshold)
                map[pixelNumber] = densitySumThreshold;
            
            // Map value to color
            float c = map[y * w + x] / densitySumThreshold;
                                    
            if (c >= 0 && c < colorThreshold)
                painter.setPen(
                    QColor(
                        (int)((c/colorThreshold) * 255),
                        0.0,
                        0.0
                    )
                );
            
            if (c > colorThreshold)
                painter.setPen(
                    QColor(
                        255,
                        (int)(255 * (c - colorThreshold)/(1 - colorThreshold)),
                        (int)(255 * (c - colorThreshold)/(1 - colorThreshold))
                    )
                );

            // Draw pixel
            painter.drawPoint(QPoint(x, y));
        }
    }

    // Update image
    m_imageItem->setPixmap(image);

    // Destroy temporary map
    delete [] map;
}
