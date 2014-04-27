// ======================================
// 3D Computergrafik
// moodle.hpi3d.de
// ======================================
// 
// Sommersemester 2014 - Aufgabenblatt 1
//                     - Aufgabe 4b
//
//
//
// ======================================

#include "exercise4b.h"
#include "stable.h"

//
// Qt
//
#include <QGraphicsPixmapItem>
#include <QGraphicsRectItem>
#include <QTimer>
#include <QPainter>
#include <iostream>
//
// STL
//
#include <math.h>

using namespace Qt;

//[-------------------------------------------------------]
//[ Definitions                                           ]
//[-------------------------------------------------------]
const float maxAbsSquare = 4.0f;
const int maxIterations  = 100;


//[-------------------------------------------------------]
//[ Helper functions                                      ]
//[-------------------------------------------------------]
namespace exercise4b {

int computeIterations(float cx, float cy) {
	
	int iterationCount = 0;
    float absSquare = 0,
		xtemp,
		x = 0,
		y = 0;

	while (x*x + y*y < maxAbsSquare && iterationCount < maxIterations) {
		xtemp = x*x - y*y + cx;
		y = 2*x*y + cy;
		x = xtemp;
		iterationCount++;
	}

	return iterationCount;
}

QColor chooseColor(int value, int max)
{
	float p = (float)value/max;
	int i = (int)(299 * std::min(std::max(p, 0.0f), 1.0f));
	int k = i / 60;
	float m = 1.0f * (i % 60) / 59.0f;
	switch (k)
	{
		case 0: return QColor(255, m*255, 0);
		case 1: return QColor((1-m)*255, 255, 0);
		case 2: return QColor(0, 255, m);
		case 3: return QColor(m*255, (1-m)*255, 255);
		case 4: return QColor((1-m)*255, 0, 255);
	}

	return QColor(0, 0, 0);
}

}

using namespace exercise4b;

Exercise4b::Exercise4b(QWidget *parent) :
    ImageView(parent),
    m_currentLevel(0),
    m_currentDir(1) {
		
    // Render mandelbrot set (initially)
    renderMandelbrot();

    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(onTimer()));
    timer->start(500);
}

Exercise4b::~Exercise4b()
{
    // Destroy timer
    delete m_timer;
}

void Exercise4b::renderMandelbrot()
{
    // Create image
    int width = 800, height = 600;
    QPixmap mandelbrot(width, height);
    QPainter painter(&mandelbrot);

    // Draw image using a quadtree
    drawRecursive(painter, 0, 0, width, height, m_currentLevel);

    // Update image
    this->setImage(mandelbrot.toImage());
}

/**
*  @brief
*    Draw function recursively by using a quadtree-method
*/
void Exercise4b::drawRecursive(QPainter &painter, int x, int y, int w, int h, int level) {
    
	if (level == 0) {
		int width = 800, height = 600;
		float cx, cy;
	    QPoint origin(600, 300);
	    float scaleX = 3.0f, scaleY = 3.0f;
	    int iterationCount;
		int middle_X = x + w/2;
		int middle_Y = y + h/2;
		cx = ((float)(middle_X - origin.x()) / width)  * scaleX; 
		cy = ((float)(middle_Y - origin.y()) / height) * scaleY;
        // Compute number of iterations
        iterationCount = computeIterations(cx, cy);
        // Get color
        QColor color = chooseColor(iterationCount, maxIterations);
		// Draw all Pixel
	    for (int i=x; i<=x+w; i++) {
	    	for (int j=y; j<=y+h; j++) {
	            painter.setPen(color);
	            painter.drawPoint(i, j);
			}
		}
		
	} else {
		level--;
		// Draw quadrants
		drawRecursive(painter, x, y, w/2, h/2, level); // Northwest
		drawRecursive(painter, x+w/2 + 1, y, w/2, h/2, level); // Northeast
		drawRecursive(painter, x, y+h/2 + 1, w/2, h/2, level); // Soutwest
		drawRecursive(painter, x+w/2 + 1, y+h/2 + 1, w/2, h/2, level); // Southeast
	}
   	

}

void Exercise4b::onTimer()
{
    if (m_currentLevel > 8) // Should be 12 but performance is to bad then
		m_currentLevel = 0;
	else
		m_currentLevel++;

    renderMandelbrot();
}
