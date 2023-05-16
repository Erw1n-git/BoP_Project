#ifndef BOARD_H
#define BOARD_H

#include <iostream>
#include <string>
#include <memory>
#include <functional>
#include <map>
#include <ctime>
#include <random>


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
        // функція з'єднання двох кубів
        void mergeCubes(std::shared_ptr<Cube>& cube, std::shared_ptr<Cube>& cube2, bool* isCube2048);

        // функція перевірки наявності можливих рухів кубів
        bool hasAvailableMoves();

    public:
        // двовимірний масив векторів для розміщения кубів
        std::vector<std::vector<std::shared_ptr<Cube>>> grid;

        Board(float xCenter, float yCenter, float zCenter,
            float xSize, float ySize, float zSize,
            float *diffColor, float *ambiColor, float *specColor);
        
        virtual void draw();
        
        void createMenu();
        void addRandomCube();
        int moveCubes(int directions);  // Рухає куби у заданому напрямку
                                        // повертає -1, якщо куби не можуть рухатись
                                        // повертає 0, якщо куби можуть рухатись
                                        // повертає 1, якщо на полі є куб зі значенням 2048

        // функція очищенная масиву кубів
        void resetGrid();

        // функція виводу сітки положень кубів у консоль
        void printGrid();

    };

}
#endif