// ======================================
// 3D-Computergrafik
// moodle.hpi3d.de
// ======================================
// 
// Sommersemester 2014 - Aufgabenblatt 1
//                     - Aufgabe 1,2,3
//
//
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

//
// STL
//
#include <math.h>

using namespace Qt;

//[-------------------------------------------------------]
//[ Helper functions                                      ]
//[-------------------------------------------------------]
// Get pixel at position
QColor Exercise123::getPixel(const QImage &image, int x, int y)
{
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

    //TODO: Implement grayscale function

    return gray;
}

// return grayscale
QColor Exercise123::getInvertColor(float r, float g, float b)
{
    //////////////////////////////////////////////////
    // Aufgabe 1 (invert color)
    //////////////////////////////////////////////////
    QColor invert;

    //TODO: Implement invert color function

    return invert;
}


//[-------------------------------------------------------]
//[ Filter functions                                      ]
//[-------------------------------------------------------]

QColor Exercise123::getSharpenColor(const QImage &image, int x, int y)
{
    //////////////////////////////////////////////////
    // Aufgabe 2
    //////////////////////////////////////////////////

    QColor color = getPixel(image, x, y);
    float r = 0;
    float g = 0;
    float b = 0;

    ///	...	 ... ... ... ...
    ///	...	|_1_|_2_|_3_|...
    ///	...	|_4_|_5_|_6_|...	<- 3x3 filter components
    ///	...	|_7_|_8_|_9_|...
    ///	...	 ... ... ... ...

    //////////////////////////////////////////////////////////////////////////
    // TODO: Define filter kernel as Laplace-Operator
    //////////////////////////////////////////////////////////////////////////

    int kernel[] = {1, 1, 1, 1, 1, 1, 1, 1, 1};

    //////////////////////////////////////////////////
    // TODO: Aufgabe 2a
    //////////////////////////////////////////////////

    // Apply kernel
    /*
    for (int yy=-1; yy<=1; yy++) {
        for (int xx=-1; xx<=1; xx++) {
            QColor pixel = getPixel(...);
            r += ...
            g += ...
            b += ...
        }
    }
    */

    clampColor(r, g, b);

    return QColor(r * 255.0f, g * 255.0f, b * 255.0f);
}

QColor Exercise123::getGaussColor(const QImage &image, int x, int y)
{
    //////////////////////////////////////////////////
    // Aufgabe 2
    //////////////////////////////////////////////////

    QColor color = getPixel(image, x, y);
    float r = 0.0;
    float g = 0.0;
    float b = 0.0;

    //////////////////////////////////////////////////////////////////////////
    // TODO: Define filter kernel as Gauss-Operator
    //////////////////////////////////////////////////////////////////////////

    int kernel[] = {1, 1, 1, 1, 1, 1, 1, 1, 1};

    // Apply kernel

    //////////////////////////////////////////////////
    // TODO: Aufgabe 2b
    //////////////////////////////////////////////////

    clampColor(r, g, b);

    return QColor(r * 255.0f, g * 255.0f, b * 255.0f);
}

QColor Exercise123::getSobelColor(const QImage &image, int x, int y)
{
    //////////////////////////////////////////////////
    // Aufgabe 2
    //////////////////////////////////////////////////

    QColor color = getPixel(image, x, y);

    //////////////////////////////////////////////////////////////////////////
    // TODO: Define filter kernels as Sobel Operators for both directions
    //////////////////////////////////////////////////////////////////////////
    int kernelX[] = {1, 1, 1, 1, 1, 1, 1, 1, 1};
    int kernelY[] = {1, 1, 1, 1, 1, 1, 1, 1, 1};

    //////////////////////////////////////////////////
    // TODO: Aufgabe 2c
    //////////////////////////////////////////////////

    // apply kernel, use grayColor()!

    float c;
    float dummy = 0.0;
    clampColor(c, dummy, dummy);

    return QColor(c * 255.0f, c * 255.0f, c * 255.0f);
}

QColor Exercise123::getMeanColorDynamicSize(const QImage &image, int x, int y, int kernelSize)
{
    //////////////////////////////////////////////////
    // Aufgabe 2
    //////////////////////////////////////////////////

    QColor color = getPixel(image, x, y);
    float r = 0.0;
    float g = 0.0;
    float b = 0.0;

    //////////////////////////////////////////////////
    // TODO: Aufgabe 2d
    //////////////////////////////////////////////////

    // Apply kernel
    /*
    float sum = 0.0;
    for (int yy=-(int)kernelSize; yy<=(int)kernelSize; yy++) {
        for (int xx=-(int)kernelSize; xx<=(int)kernelSize; xx++) {
            //
        }
    }
    */

    // TODO: normalize

    clampColor(r, g, b);

    return QColor(r * 255.0f, g * 255.0f, b * 255.0f);
}

//getDitheringColor can work directly on image - use it
QColor Exercise123::getDitheringColor(QImage &image, int x, int y)
{
    //////////////////////////////////////////////////
    // Aufgabe 3
    //////////////////////////////////////////////////

    float oldpixel, newpixel;

    //TODOD: dithering by floyd-steinberg



    clampColor(newpixel,newpixel,newpixel);
    return QColor(newpixel * 255.0f,newpixel * 255.0f,newpixel * 255.0f);
}

Exercise123::Exercise123(Filter_Type type, QWidget *parent) :
    ImageView(parent),
    m_type(type)
{
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
