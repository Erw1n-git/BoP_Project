#ifndef SCENE_H
#define SCENE_H

#include <stdio.h>
#include <memory>

#include <GL/glut.h>

#include "Score.h"
#include "Shapes/Board.h"
#include "Shapes/Cube.h"
#include "Shapes/Shape.h"
#include "Utils/Utils.h"

#define _CRT_SECURE_NO_WARNINGS

namespace Game
{

    // Основний клас гри, який представляє геометрію сцени,
    // контролює правила гри, розташування елементів,
    // а також реалізує обробку подій GLUT
    class Scene
    {

    private:
        std::shared_ptr<Board> board; // вказівник на об'єкт Board

        int button;           // кнопка миші (-1 - не натиснута, 0 - ліва, 2 - права)
        float angleX, angleY; // поточний кут повороту сцени 
        float mouseX, mouseY; // поточні координати
        float width, height;  // Розміри вікна
        float distZ;          // відстань по осі Z до сцени
        float xStep, zStep;   // відстань між окремими стрижнями
        int time;             // поточний час у секуднах
        int xFrom, zFrom;     // індекси стрижня, з якого починається пересування
        int xTo, zTo;         // індекси стрижня, яким закінчується пересування

        // стан гри: (-1) - гру програно, (0) - гра не завершена,
        // (1) - гру виграно, (2) - головне меню
        int gameState;  

        void initialize();
        bool findNearest(int x, int z, int& x1, int& z1);

    public:
        Scene(float xStep, float zStep);

        void on_paint();
        void on_size(int width, int height);
        void on_mouse(int button, int state, int x, int y);
        void on_motion(int x, int y);
        void on_keyboard(unsigned char key, int x, int y);
        void on_special(int key, int x, int y);
        void on_timer(int value);

        void on_win();
        void on_lose();
        void on_menu(int selection_id);
    };

}

#endif