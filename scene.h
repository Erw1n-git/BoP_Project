#ifndef Scene_h
#define Scene_h

#include "shape.h"
#include "disk.h"
#include <vector>

namespace DiskGame
{

    const int M = 3, N = 3; // кількість рядків та колонок поля

                            // Основний клас гри, який представляє геометрію сцени,
                            // контролює правила гри, розташування елементів,
                            // а також реалізує обробку подій GLUT
    class Scene
    {
        std::vector<Shape*> shapes; // "гнучкий" масив указівників на елементи гри
        int button;           // кнопка миші (-1 - не натиснута, 0 - ліва, 2 - права)
        float angleX, angleY; // поточний кут повороту сцени 
        float mouseX, mouseY; // поточні координати
        float width, height;  // Розміри вікна
        float distZ;          // відстань по осі Z до сцени
        bool finish;          // ознака того, що гру завершено
        Disk *disks[N];       // масив указівників на диски
        float xStep, zStep;   // відстань між окремими стрижнями
        int time;             // поточний час у секуднах
        int fields[M][N];     // масив, у якому відображається розміщення дисків:
                              // 0 - диску немає, 
                              // 1, 2, 3 - червоний, жовтий та зелений диски відповідно
        int xFrom, zFrom;     // індекси стрижня, з якого починається пересування
        int xTo, zTo;         // індекси стрижня, яким закінчується пересування
    public:
        Scene(float xStep, float zStep);
        ~Scene();
        void on_paint();
        void on_size(int width, int height);
        void on_mouse(int button, int state, int x, int y);
        void on_motion(int x, int y);
        void on_special(int key, int x, int y);
        void on_timer(int value);
    private:
        void initialize();
        void allocateDisks();
        bool moveDisk(int xFrom, int zFrom, int xTo, int zTo);
        void upDisk(int x, int z);
        void downAllDisks();
        bool findNearest(int x, int z, int& x1, int& z1);
        void resetArr();
        float allocX(int i);
        float allocZ(int i);
    };

}

#endif