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
        std::string getValue() const;

        void setGridCoords(int x, int z);
        void setMerged(bool merged);

        int getGridX() const;
        int getGridZ() const;
        bool isMerged() const;

        void updateColor();

        void setPosition(float x, float y, float z);

        void hitTest() const;
    };
}
#endif