#ifndef CUBE_H
#define CUBE_H

#include <string>
#include <GL/glut.h>

#include "Shape.h"
#include "../Utils.h"

namespace Game
{
    // Клас, який відповідає за малювання стрижня
    using namespace GraphUtils;
     
    class Cube : public Shape
    {
    private:
        int board_grid_x;
        int board_grid_y;
        unsigned int textValue;
        bool merged;

    public:
        Cube(float xCenter, float yCenter, float zCenter,
            float xSize, float ySize, float zSize,
            int board_grid_x, int board_grid_y, unsigned int textValue);
        virtual void draw();

        void setTextValue(unsigned int textValue);
        unsigned int getTextValue() const;

        void setBoardGrid(int x, int y);
        void setMerged(bool merged);

        int getBoardGridX() const;
        int getBoardGridY() const;
        bool isMerged() const;

        void updateColor();

        void setPosition(float x, float y, float z);
    };
}
#endif