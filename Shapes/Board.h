#ifndef BOARD_H
#define BOARD_H

#include <GL/glut.h>

#include "Shape.h"
#include "../Utils.h"

namespace DiskGame
{
    // Клас, який відповідає за малювання дошки (поля гри)
    class Board : public Shape
    {
    public:
        Board(float xCenter, float yCenter, float zCenter,
            float xSize, float ySize, float zSize,
            float *diffColor, float *ambiColor, float *specColor)
            : Shape(xCenter, yCenter, zCenter,
                xSize, ySize, zSize,
                specColor, diffColor, ambiColor) { }
        virtual void draw();
    };

}
#endif