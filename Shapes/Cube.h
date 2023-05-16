#ifndef CUBE_H
#define CUBE_H

#include <string>
#include <GL/glut.h>

#include "Shape.h"
#include "../Utils/Utils.h"

namespace Game
{
    // Клас, який відповідає за малювання стрижня
    using namespace GraphUtils;

    class Cube : public Shape
    {
    private:
        int gridX;
        int gridZ;
        std::string value;
        bool merged;

    public:
        Cube(float xCenter, float yCenter, float zCenter,
             float xSize, float ySize, float zSize,
             int gridX, int gridZ, std::string value);
             
        virtual void draw();

        void setValue(std::string value);
        std::string getValue() const { return value; }

        void setGridCoords(int x, int z);
        int getGridX() const { return gridX; } 
        int getGridZ() const { return gridZ; }

        void setMerged(bool merged) { this->merged = merged; }
        bool isMerged() const { return merged; }

        void updateColor();
    };
}
#endif