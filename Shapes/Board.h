#ifndef BOARD_H
#define BOARD_H

#include <memory>
#include <functional>
#include <map>
#include <ctime>
#include <random>
#include <cstdlib>

#include <iostream>

#include <GL/glut.h>

#include "Shape.h"
#include "Cube.h"
#include "../Score.h"
#include "../Utils/Utils.h"

#define MOVE_CUBES_UP 0
#define MOVE_CUBES_DOWN 1
#define MOVE_CUBES_LEFT 2
#define MOVE_CUBES_RIGHT 3

namespace Game
{
    // Клас, який відповідає за малювання дошки (поля гри)

    class Board : public Shape
    {

    private:
        std::vector<std::vector<std::shared_ptr<Cube>>> grid; // двовимірний масив векторів для розміщения кубів

        void mergeCubes(std::shared_ptr<Cube>& cube, std::shared_ptr<Cube>& cube2, bool* isCube2048);
        bool hasAvailableMoves();

    public:
        /*Board(float xCenter, float yCenter, float zCenter,
            float xSize, float ySize, float zSize,
            float *diffColor, float *ambiColor, float *specColor)
            : Shape(xCenter, yCenter, zCenter,
                xSize, ySize, zSize,
                specColor, diffColor, ambiColor) { }*/

        Board(float xCenter, float yCenter, float zCenter,
            float xSize, float ySize, float zSize,
            float *diffColor, float *ambiColor, float *specColor);
        
        virtual void draw();

        void addRandomCube();
        int moveCubes(int directions);  // Рухає куби у заданому напрямку
                                        // повертає -1, якщо куби не можуть рухатись
                                        // повертає 0, якщо куби можуть рухатись
                                        // повертає 1, якщо на полі є куб зі значенням 2048

        void resetGrid();
        void printGrid();
        //std::vector<std::vector<std::shared_ptr<Cube>>> getGrid() { return grid; }
        //void setGrid(std::vector<std::vector<std::shared_ptr<Cube>>> grid) { this->grid = grid;}

    protected:
    };

}
#endif