#include "Scene.h"

namespace Game
{
    using namespace GraphUtils;

    // Параметри конструктора - відстань між окремими стрижнями:
    Scene::Scene(float xStep, float zStep)
    {
        this->xStep = xStep;
        this->zStep = zStep;

        // Додаємо дошку сірого кольору. 
        // Розміри визначаємо так, щоб поміщалися всі стрижні:
        shapes.push_back(new Board(0.0, 0.0, 0.0, N * xStep + 0.2, 0.1, M * xStep + 0.2, diffBoardColor, ambiBoardColor, specBoardColor));
        // Додаємо стрижні (крім останнього ряду):
        for (int i = 0; i < M; i++)
        {
            for (int j = 0; j < N; j++)
            {
                shapes.push_back(new Cube(allocX(j), 0.15, allocZ(i), 0.2, 0.2, 0.2, diffGray, ambiGray, specGray, 1024));
            }
        }

        // !
        // Додаємо останній ряд стрижнів:
        // shapes.push_back(new Cube(allocX(0), 0.15, allocZ(M - 1), 0.1, 0.1, 0.1, diffRed, ambiRed, specRed, 256));
        // shapes.push_back(new Cube(allocX(1), 0.15, allocZ(M - 1), 0.1, 0.1, 0.1, diffYellow, ambiYellow, specYellow, 256));
        // shapes.push_back(new Cube(allocX(2), 0.15, allocZ(M - 1), 0.1, 0.1, 0.1, diffGreen, ambiGreen, specGreen, 256));
        // ! 
        // Додаємо диски в першому ряду:
        //shapes.push_back(disks[0] = new Disk(allocX(0), 0.1, allocZ(0), 0.3, 0.1, 0.3, diffRed, ambiRed, specRed, 0.05));
        //shapes.push_back(disks[1] = new Disk(allocX(1), 0.1, allocZ(0), 0.3, 0.1, 0.3, diffYellow, ambiYellow, specYellow, 0.05));
        //shapes.push_back(disks[2] = new Disk(allocX(2), 0.1, allocZ(0), 0.3, 0.1, 0.3, diffGreen, ambiGreen, specGreen, 0.05));
        
        // Здійснюємо ініціалізацію параметрів перед першою грою:
        initialize();
    }

    Scene::~Scene()
    {
        // Видаляємо всі фігури:
        for (int i = 0; i < shapes.size(); i++)
        {
            delete shapes[i];
        }
    }

    // ! 
    /*
    // Ініціалізація масиву, в якому відображається розміщення дисків
    void Scene::resetArr()
    {
        // Спочатку всі диски в першому ряду:
        for (int j = 0; j < N; j++)
        {
            fields[0][j] = j + 1;
        }
        // Інші стрижні поки порожні:
        for (int i = 1; i < M; i++)
        {
            for (int j = 0; j < N; j++)
            {
                fields[i][j] = 0;
            }
        }
    } */
    
    // Перерахування індексу масиву fields в координату x
    float Scene::allocX(int i)
    {
        return  xStep * i - (N - 1) * xStep / 2;
    }

    // Перерахування індексу масиву fields в координату z
    float Scene::allocZ(int i)
    {
        return  zStep * i - (M - 1) * zStep / 2;
    }

    // !
    /*
    // Розташування дисків відповідно до вмісту масиву fields
    void Scene::allocateDisks()
    {

        // ! DEBUG
        std::cout << "this is a test (1)" << std::endl;

        for (int i = 0; i < M - 1; i++)
        {
            for (int j = 0; j < N; j++)
            {
                if (fields[i][j] > 0)
                {
                    disks[fields[i][j] - 1]->setCoords(allocX(j), 0.1, allocZ(i));
                }
            }
        }
    }

    // Переміщення диску зі вказаної позиції на нову
    bool Scene::moveDisk(int xFrom, int zFrom, int xTo, int zTo)
    {
        // Перевірка можливості переміщення:
        if (xFrom < 0 || zFrom < 0 || xFrom >= N || zFrom >= M || fields[zFrom][xFrom] == 0)
        {
            return false;
        }
        if (xTo < 0 || zTo < 0 || xTo >= N || zTo >= M || fields[zTo][xTo] > 0)
        {
            return false;
        }
        if (xFrom == xTo && zFrom == zTo)
        {
            return false;
        }
        if (xFrom != xTo && zFrom != zTo)
        {
            return false;
        }
        if (xFrom - xTo > 1 || xTo - xFrom > 1 || zFrom - zTo > 1 || zTo - zFrom > 1)
        {
            return false;
        }
        if (disks[fields[zFrom][xFrom] - 1]->getYCenter() < 0.2)
        {
            return false;
        }

        // Переміщення:
        disks[fields[zFrom][xFrom] - 1]->setXCenter(allocX(xTo));
        disks[fields[zFrom][xFrom] - 1]->setZCenter(allocZ(zTo));
        // Внесення змін в дані масиву fields:
        fields[zTo][xTo] = fields[zFrom][xFrom];
        fields[zFrom][xFrom] = 0;
        return true;
    }

    // Підняття догори диску, розташованому на стрижні з відповідними координатами
    void Scene::upDisk(int x, int z)
    {
        if (x < 0 || z < 0 || x >= N || z >= M)
        {
            return;
        }
        if (fields[z][x] > 0)
        {
            disks[fields[z][x] - 1]->setYCenter(0.3);
        }
    }

    // Опускання всіх дисків
    void Scene::downAllDisks()
    {
        for (int i = 0; i < N; i++)
        {
            disks[i]->setYCenter(0.1);
        }
    }
    */ // !

    // Ініціалізація даних (виконується спочатку, а потім з кожним оновленням гри):
    void Scene::initialize()
    {
        // !
        /*
        resetArr();      // початкове заповнення масиву fields
                         // "Тасування" масиву. Оскільки двовимірний масив у C++ зберігається як 
                         // одновимірний, здійснюємо його приведення до типу одновимірного масиву:
        GraphUtils::shuffle((int *)fields, (M - 1) * N);
        allocateDisks(); // розташування дисків відповідно до масиву fields
        */

        // Ініціалізація елементів даних:
        distZ = -1.7;
        angleX = -10;
        angleY = 30;
        time = 0;
        finish = false;
    }

    // Пошук стрижня, найближчого до позиції курсору миші:
    bool Scene::findNearest(int x, int y, int& x1, int& z1)
    {
        int viewport[4];
        int iMin = -1, jMin = -1;
        double mvMatrix[16], projMatrix[16];
        double minDist = 2000;

        for (int i = 0; i < M; i++)
        {
            for (int j = 0; j < N; j++)
            {

                // Світові x, y, z поточного стрижня:
                double wx = allocX(j);
                double wy = 0.1;
                double wz = allocZ(i);

                // Заповнюємо масив viewport поточною областю перегляду:
                glGetIntegerv(GL_VIEWPORT, viewport);

                // Заповнюємо масиви поточними матрицями:
                glGetDoublev(GL_MODELVIEW_MATRIX, mvMatrix);
                glGetDoublev(GL_PROJECTION_MATRIX, projMatrix);

                // Світові x, y, z координати, що обертаються:
                double dx, dy, dz;

                // Отримуємо координати точки, на яку спроектовано поточний стрижень:
                gluProject(wx, wy, wz, mvMatrix, projMatrix, viewport, &dx, &dy, &dz);
                dy = viewport[3] - dy - 1; // dy необхідно перерахувати
                double d = (x - dx) * (x - dx) + (y - dy) * (y - dy); // квадрат відстані
                if (d < minDist) // знайшли ближчий стрижень
                {
                    minDist = d;
                    iMin = i;
                    jMin = j;
                }
            }
        }
        if (minDist < 1000) // знайшли найближчий стрижень
        {
            x1 = jMin;
            z1 = iMin;
            return true;
        }
        else
        {
            return false;
        }
    }

    // Оброблювач події, пов'язаної з перемалюванням вікна
    void Scene::on_paint()
    {
        char text[128]; // Масив символів, 
                        // Заповнення масиву символів відповідно до стану гри:
        if (finish)
        {
            sprintf(text, "Game over. Time: %d sec.   F2 - Restart game   Esc - Exit", time);
        }
        else
        {
            sprintf(text, "F2 - Restart game   Esc - Exit              Time: %d sec.", time);
        }
        // Встановлюємо область перегляду таку, щоб вона вміщувала все вікно:
        glViewport(0, 0, width, height);

        // Ініціалізуємо параметри матеріалів і джерела світла:
        float lightAmbient[] = { 0.0f, 0.0f, 0.0f, 1.0f }; // колір фонового освітлення 
        float lightDiffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f }; // колір дифузного освітлення 
        float lightSpecular[] = { 1.0f, 1.0f, 1.0f, 1.0f };// колір дзеркального відображення
        // ! float lightPosition[] = { 0.0f, 1.0f, 1.0f, 0.0f };// розташування джерела світла
        float lightPosition[] = { -1.0f, 2.0f, 1.0f, 0.0f };// розташування джерела світла

        // Встановлюємо параметри джерела світла:
        glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmbient);
        glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiffuse);
        glLightfv(GL_LIGHT0, GL_SPECULAR, lightSpecular);
        glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);

        // Визначаємо блакитний колір для очищення:
        if (finish)
        {
            // ! glClearColor(0, 0.7, 0.7, 0);
            glClearColor(0.98, 0.92, 0.94, 0);
        }
        else
        {
            // ! glClearColor(0, 0.5, 0.5, 0);
            glClearColor(0.98, 0.92, 0.94, 0);
        }

        // Очищуємо буфери:
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glPushMatrix();
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();

        // Для відображення тексту, краще використовувати ортографічну проекцію:
        glOrtho(0, 1, 0, 1, -1, 1);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        glColor3f(1, 1, 0); // жовтий текст
        drawString(GLUT_BITMAP_TIMES_ROMAN_24, text, 0.01, 0.95);
        glPopMatrix();

        // Включаємо режим роботи з матрицею проекцій:
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();

        // Задаємо усічений конус видимості в лівосторонній системі координат, 
        // 60 - кут видимості в градусах по осі у,
        // width/height - кут видимості уздовж осі x,
        // 1 и 100 - відстань від спостерігача до площин відсікання по глибині:
        gluPerspective(60, width / height, 1, 100);

        // Включаємо режим роботи з видовою матрицею:
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        glTranslatef(0, 0, distZ);	// камера з початку координат зсувається на distZ, 

        glRotatef(angleX, 0.0f, 1.0f, 0.0f);  // потім обертається по осі Oy
        glRotatef(angleY, 1.0f, 0.0f, 0.0f);  // потім обертається по осі Ox
        glEnable(GL_DEPTH_TEST);	// включаємо буфер глибини (для відсікання невидимих частин зображення)

                                    // Включаємо режим для установки освітлення:
        glEnable(GL_LIGHTING);

        // Додаємо джерело світла № 0 (їх може бути до 8), зараз воно світить з "очей":
        glEnable(GL_LIGHT0);

        // Малюємо усі фігури:
        for (int i = 0; i < shapes.size(); i++)
        {
            shapes[i]->draw();
        }

        // Вимикаємо все, що включили:
        glDisable(GL_LIGHT0);
        glDisable(GL_LIGHTING);
        glDisable(GL_DEPTH_TEST);
        glFlush();
        // показуємо вікно:
        glutSwapBuffers(); // перемикання буферів
    }

    // Оброблювач події, пов'язаної зі зміною розмірів вікна 
    void Scene::on_size(int width, int height)
    {
        this->width = width;
        if (height == 0)
            height = 1;
        this->height = height;
    }

    // Оброблювач подій, пов'язаних з натисканням кнопок миші
    void Scene::on_mouse(int button, int state, int x, int y)
    {
        // Зберігаємо поточні координати миші:
        mouseX = x;
        mouseY = y;

        if ((state == GLUT_UP)) // кнопка віджата
        {
            // ! 
            /*
            downAllDisks();
            // Перевірка закінчення гри:
            if (fields[M - 1][0] == 1 && fields[M - 1][1] == 2 && fields[M - 1][2] == 3)
            {
                finish = true;
            }
            this->button = -1;  // ніяка кнопка не натиснута
            */
            return;
        }
        this->button = button;  // зберігаємо інформацію про кнопки
        if (finish)
        {
            return;
        }
        // Вибираємо диск для пересування:
        if (button == 0 && findNearest(x, y, xFrom, zFrom))
        {
            // ! upDisk(xFrom, zFrom);
        }
    }

    // Оброблювач подій, пов'язаних з пересуванням миші з натисненою кнопкою
    void Scene::on_motion(int x, int y)
    {
        switch (button)
        {
        // !
        /*
        case 0: // ліва кнопка - пересування диску
            if (finish)
                break;
            if (findNearest(x, y, xTo, zTo))
            {
                moveDisk(xFrom, zFrom, xTo, zTo);
                xFrom = xTo;
                zFrom = zTo;
            }
            break;
        */
        case 2: // права кнопка - обертання сцени
            angleX += x - mouseX;
            angleY += y - mouseY;
            mouseX = x;
            mouseY = y;
            break;
        }
        
    }

    // Оброблювач подій, пов'язаних з натисненням функціональних клавіш і стрілок 
    void Scene::on_special(int key, int x, int y)
    {
        switch (key) {
        case GLUT_KEY_UP:   // наближення
            if (distZ > -1.7)
            {
                break;
            }
            distZ += 0.1;
            break;
        case GLUT_KEY_DOWN: // віддалення
            distZ -= 0.1;
            break;
        case GLUT_KEY_F2:   // нова гра
            initialize();
            break;
        }
    }

    int tick = 0; // лічильник, значення якого змінюється кожні 25 мс

                  // Оброблювач події від таймера
    void Scene::on_timer(int value)
    {
        tick++;
        if (tick >= 40) // нарахували наступну секунду
        {
            if (!finish)// секунди нарощуються, якщо гру не закінчено
            {
                time++;
            }
            tick = 0;   // скинули лічильник
        }
        on_paint();     // здійснюємо перемалювання вікна
    }

}