#include "Shape.h"
 
namespace Game
{
 
    // Конструктор
    Shape::Shape(float xCenter, float yCenter, float zCenter,
                 float xSize, float ySize, float zSize,
                 float *diffColor, float *ambiColor, float *specColor)
    {
        setCoords(xCenter, yCenter, zCenter);
        setSize(xSize, ySize, zSize);
        setColors(diffColor, ambiColor, specColor);
    }

    // Функції доступу

    void Shape::setCoords(float xCenter, float yCenter, float zCenter)
    {    
        this->xCenter = xCenter;
        this->yCenter = yCenter;
        this->zCenter = zCenter;
    }

    void Shape::setSize(float xSize, float ySize, float zSize)
    {
        this->xSize = xSize;
        this->ySize = ySize;
        this->zSize = zSize;
    }

    void Shape::setColors(float* diffColor, float* ambiColor, float* specColor)
    {
        this->diffColor = diffColor;
        this->ambiColor = ambiColor;
        this->specColor = specColor;
    }

}