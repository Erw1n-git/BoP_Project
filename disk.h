#ifndef Disk_h
#define Disk_h

#include "shape.h"

namespace DiskGame
{
    // Клас, який відповідає за малювання диска
    class Disk : public Shape
    {
    private:
        float innerRadius;
    public:
        Disk(float xCenter, float yCenter, float zCenter,
            float xSize, float ySize, float zSize,
            float *diffColor, float *ambiColor, float *specColor,
            float innerRadius)
            : Shape(xCenter, yCenter, zCenter, xSize, ySize, zSize,
                specColor, diffColor, ambiColor) {
            this->innerRadius = innerRadius;
        }
        float getInnerRadius() const { return innerRadius; }
        void setInnerRadius(float innerRadius) { this->innerRadius = innerRadius; }
        virtual void draw();
    };
}
#endif