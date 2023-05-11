#ifndef SCENE_H
#define SCENE_H

#include <stdio.h>
#include <vector>
#include <memory>

#include <GL/glut.h>

//#include "Scene.h"
#include "Score.h"
#include "Utils/Utils.h"
#include "Shapes/Board.h"
#include "Shapes/Cube.h"
#include "Shapes/Shape.h"
#include "Shapes/Disk.h"

#define _CRT_SECURE_NO_WARNINGS

namespace Game
{

    // Основний клас гри, який представляє геометрію сцени,
    // контролює правила гри, розташування елементів,
    // а також реалізує обробку подій GLUT
    class Scene
    {

    private:
        // ! std::vector<std::shared_ptr<Shape>> shapes; // "гнучкий" масив "умних" указівників на елементи гри
        std::shared_ptr<Board> board; // вказівник на об'єкт Board

        int button;           // кнопка миші (-1 - не натиснута, 0 - ліва, 2 - права)
        float angleX, angleY; // поточний кут повороту сцени 
        float mouseX, mouseY; // поточні координати
        float width, height;  // Розміри вікна
        float distZ;          // відстань по осі Z до сцени
        // ! bool finish;          // ознака того, що гру завершено
        int gameState;  // стан гри: (-1) - гру програно, (0) - гра не завершена (1) - гру виграно 
        
        
        //Score score;

        // !
        /*
        Disk *disks[N];       // масив указівників на диски
        */

        float xStep, zStep;   // відстань між окремими стрижнями
        int time;             // поточний час у секуднах

        // !
        /*int fields[M][N];     // масив, у якому відображається розміщення дисків:
                              // 0 - диску немає, 
                              // 1, 2, 3 - червоний, жовтий та зелений диски відповідно
        */
        int xFrom, zFrom;     // індекси стрижня, з якого починається пересування
        int xTo, zTo;         // індекси стрижня, яким закінчується пересування

        void initialize();
        // ! void allocateDisks();
        // ! bool moveDisk(int xFrom, int zFrom, int xTo, int zTo);
        // ! void upDisk(int x, int z);
        // ! void downAllDisks();
        // float allocX(int i);
        // float allocZ(int i);
        bool findNearest(int x, int z, int& x1, int& z1);
        void resetArr();

        void on_win();
        void on_lose();

    public:

        Scene(float xStep, float zStep);
        // ! ~Scene();
        void on_paint();
        void on_size(int width, int height);
        void on_mouse(int button, int state, int x, int y);
        void on_motion(int x, int y);
        void on_keyboard(unsigned char key, int x, int y);
        void on_special(int key, int x, int y);
        void on_timer(int value);

    };

}

#endif