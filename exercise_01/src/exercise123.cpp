// ======================================
// 3D-Computergrafik
// moodle.hpi3d.de
// ======================================
// 
// Sommersemester 2014 - Aufgabenblatt 1
//                     - Aufgabe 1,2,3
//						766414 
//						768201
//
// ======================================

#include "exercise123.h"

//
// Qt
//
#include <QGraphicsView>
#include <QGraphicsPixmapItem>
#include <QGraphicsRectItem>

#include <QDebug>
#include <iostream>

//
// STL
//
#include <math.h>

using namespace Qt;

//[-------------------------------------------------------]
//[ Helper functions                                      ]
//[-------------------------------------------------------]
// Get pixel at position
QColor Exercise123::getPixel(const QImage &image, int x, int y) {
	
    int width = image.width();
    int height = image.height();

    int x_ = (x < 0 ? 0 : (x > width -1 ? width -1 : x));
    int y_ = (y < 0 ? 0 : (y > height-1 ? height-1 : y));

    return QColor(image.pixel(x_, y_));
}

// clamp color components to [0.0, 1.0]
void Exercise123::clampColor(float& r, float& g, float& b) {
	
    if (r < 0)
        r = 0.0;
    else if (r > 1.0)
        r = 1.0;

    if (g < 0)
        g = 0.0;
    else if (g > 1.0)
        g = 1.0;

    if (b < 0)
        b = 0.0;
    else if (b > 1.0)
        b = 1.0;
}

// return grayscale
float Exercise123::getGrayColor(float r, float g, float b)
{
    //////////////////////////////////////////////////
    // Aufgabe 1 (grayscale)
    //////////////////////////////////////////////////
    float gray;

    gray = 0.299 * r + 0.587 * g + 0.114 * b;

    return gray;
}

// return grayscale
QColor Exercise123::getInvertColor(float r, float g, float b)
{
    //////////////////////////////////////////////////
    // Aufgabe 1 (invert color)
    //////////////////////////////////////////////////
    QColor invert;

    invert.setRgb(255 - r, 255 - g, 255 - b);

    return invert;
}


//[-------------------------------------------------------]
//[ Filter functions                                      ]
//[-------------------------------------------------------]

QColor Exercise123::getSharpenColor(const QImage &image, int x, int y) {
		
    float r = 0, g = 0,	b = 0;
		
    int kernel[] = {
		-1, -1, -1,
		-1, 9, -1,
		-1, -1, -1
	};
	for (int yy = -1; yy <= 1; yy++) {
        for (int xx = -1; xx <= 1; xx++) {
            
			QColor pixel = getPixel(image, x + xx, y + yy);
			
			int kernelValue = kernel[(yy + 1) * 3 + (xx + 1)];
			
            r += pixel.red() * kernelValue;
            g += pixel.green() * kernelValue;
            b += pixel.blue() * kernelValue;
        }
    }
	r /= 255;
	g /= 255;
	b /= 255;
	
    clampColor(r, g, b);

    return QColor(r * 255.0f, g * 255.0f, b * 255.0f);
}


QColor Exercise123::getGaussColor(const QImage &image, int x, int y) {

    float r = 0, g = 0,	b = 0;

	int kernel[] = {
		1, 2, 1,
		2, 4, 2,
		1, 2, 1
	};
	
    // Apply kernel
	for (int yy = -1; yy <= 1; yy++) {
        for (int xx = -1; xx <= 1; xx++) {
            
			QColor pixel = getPixel(image, x + xx, y + yy);
			
			int kernelValue = kernel[(yy + 1) * 3 + (xx + 1)];
			
            r += pixel.red() * kernelValue;
            g += pixel.green() * kernelValue;
            b += pixel.blue() * kernelValue;
        }
    }
	
	r = (r / 16) / 255;
	g = (g / 16) / 255;
	b = (b / 16) / 255;
	
    clampColor(r, g, b);

    return QColor(r * 255.0f, g * 255.0f, b * 255.0f);
}


QColor Exercise123::getSobelColor(const QImage &image, int x, int y) {
	
	
	float gray1, gray2,
		dummy = 0.0;

    int kernelX[] = {
		1, 0, -1,
		2, 0, -2,
		1, 0, -1
	};
		
    int kernelY[] = {
		1, 2, 1,
		0, 0, 0,
		-1, -2, -1
	};

    // Apply kernel
	for (int yy = -1; yy <= 1; yy++) {
        for (int xx = -1; xx <= 1; xx++) {
			
			int kernelValue;
            
			QColor pixel = getPixel(image, x + xx, y + yy);
			
			kernelValue = kernelX[(yy + 1) * 3 + (xx + 1)];
		    gray1 += qGray(pixel.rgb()) * kernelValue;
			
			kernelValue = kernelY[(yy + 1) * 3 + (xx + 1)];
		    gray2 += qGray(pixel.rgb()) * kernelValue;
        }
    }
	
	float grayAll = abs(gray1) + abs(gray2);
	grayAll /= 255;

    clampColor(grayAll, dummy, dummy);

    return QColor(grayAll * 255.0f, grayAll * 255.0f, grayAll * 255.0f);
}


QColor Exercise123::getMeanColorDynamicSize(const QImage &image, int x, int y, int kernelSize) {
    
	float r = 0, g = 0,	b = 0;
	
    // Apply kernel
	for (int yy = -(int)kernelSize; yy <= (int)kernelSize; yy++) {
        for (int xx = -(int)kernelSize; xx <= (int)kernelSize; xx++) {
			            
			QColor pixel = getPixel(image, x + xx, y + yy);
			
            r += pixel.red();
            g += pixel.green();
            b += pixel.blue();
        }
    }
	
	r = (r / pow(kernelSize * 2 + 1, 2)) / 255;
	g = (g / pow(kernelSize * 2 + 1, 2)) / 255;
	b = (b / pow(kernelSize * 2 + 1, 2)) / 255;
	
    clampColor(r, g, b);

    return QColor(r * 255.0f, g * 255.0f, b * 255.0f);
}


//getDitheringColor can work directly on image - use it
QColor Exercise123::getDitheringColor(QImage &image, int x, int y) {

    float newpixel, normalizedError, oldpixel;
	QColor oldpxColor;
	
    int width = image.width();
    int height = image.height();

    float kernel[] = {
		0, 0, 0,
		0, 0, 7,
		3, 5, 1
	};

	oldpxColor = getPixel(image, x, y);
	oldpixel = Exercise123::getGrayColor(oldpxColor.red(), oldpxColor.green(), oldpxColor.blue()) / 255;
	newpixel = round(oldpixel);
	normalizedError = oldpixel - newpixel;
	
    // Apply kernel
	for (int yy = -1; yy <= 1; yy++) {
        for (int xx = -1; xx <= 1; xx++) {
			
			float kernelValue = kernel[(yy + 1) * 3 + (xx + 1)];
			
			if(kernelValue > 0 &&
				x + xx > 0 &&
				x + xx < width - 1 &&
				y + yy > 0 &&
				y + yy < height - 1) {
					
				float pixel;
				QColor pxColor, newAdjacentPixel;

				pxColor = getPixel(image, x + xx, y + yy),
				pixel = Exercise123::getGrayColor(pxColor.red(), pxColor.green(), pxColor.blue()) / 255;

				pixel += ((kernelValue / 16) * normalizedError);							
				pixel = (pixel > 1) ? 1 : (pixel < 0) ? 0 : pixel * 255;

				pxColor.setRgb(pixel, pixel, pixel);

				image.setPixel(x + xx, y + yy, pxColor.rgb());
			}
        }
    }
	

    clampColor(newpixel, newpixel, newpixel);
	
    return QColor(newpixel * 255.0f, newpixel * 255.0f, newpixel * 255.0f);
}


Exercise123::Exercise123(Filter_Type type, QWidget *parent) : ImageView(parent), m_type(type) {
   
    // load image
    const QImage image("../image1.png");
    QImage filterImage(image);

    if(type == ORIGINAL) {
        this->setImage(image);
    }
    else {
        // filter image
        for (int y=0; y<image.height(); y++) {
            for (int x=0; x<image.width(); x++) {
                QColor filteredColor;

                // choose filter
                if(type == LAPLACE) {
                    filteredColor = getSharpenColor(image, x, y);
                }
                else if(type == GAUSS) {
                    filteredColor = getGaussColor(image, x, y);
                }
                else if(type == SOBEL) {
                    filteredColor = getSobelColor(image, x, y);
                }
                else if(type == MEANFILTER) {
                    filteredColor = getMeanColorDynamicSize(image, x, y, 5);
                }
                else if(type == GRAYSCALE) {
                    QColor pixel = getPixel(image, x, y);
                    float luminance = getGrayColor(pixel.redF(), pixel.greenF(), pixel.blueF());
                    filteredColor = QColor(luminance*255, luminance*255, luminance*255);
                }
                else if(type == INVERT) {
                    QColor pixel = getPixel(image, x, y);
                    filteredColor = getInvertColor(pixel.red(),pixel.green(),pixel.blue());
                }
                else if(type == DITHERED) {
                    filteredColor = getDitheringColor(filterImage, x, y);
                }
                else {
                    // ORIGINAL -> do nothing
                }

                // draw pixel
                filterImage.setPixel(x,y,filteredColor.rgb());
            }
        }

        this->setImage(filterImage);
        this->zoomOut();
    }
}

Exercise123::~Exercise123()
{
}
