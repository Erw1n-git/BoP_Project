#ifndef CUBE_H
#define CUBE_H

#include <string>
#include <GL/glut.h>

#include "Shape.h"
#include "../Utils.h"

namespace DiskGame
{
    // Клас, який відповідає за малювання стрижня
    class Cube : public Shape
    {
    private:
        unsigned int textValue;

    public:
        Cube(float xCenter, float yCenter, float zCenter,
            float xSize, float ySize, float zSize,
            float *diffColor, float *ambiColor, float *specColor,
            unsigned int textValue);
        virtual void draw();

        void setTextValue(unsigned int textValue) { this->textValue = textValue; }
        unsigned int getTextValue() { return textValue; }
    };
}
#endif