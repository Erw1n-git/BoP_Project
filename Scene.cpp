#include "Scene.h"

namespace Game
{

    // Параметри конструктора - відстань між окремими кубами
    Scene::Scene(float xStep, float zStep)
    {
        this->xStep = xStep;
        this->zStep = zStep;

        gameState = 2;

        initialize();
    }

    // Ініціалізація даних (виконується спочатку, а потім з кожним оновленням гри)
    void Scene::initialize()
    {
        angleX = 2;
        angleY = 77;
        time = 0;

        // Створення поля гри, в залежності від стану гри
        // Якщо 2, то створюємо меню вибіру розмірів поля
        if (gameState != 2)
        {
            distZ = -1.7;

            board = std::make_shared<Board>(0.0, 0.0, 0.0, N * xStep + 0.2, 0.1, M * xStep + 0.2, diffBoardColor, ambiBoardColor, specBoardColor);
            board->resetGrid();
            board->addRandomCube();
            board->addRandomCube();
        }
        else
        {
            distZ = -1.3;

            board = std::make_shared<Board>(0.0, 0.0, 0.0, 999, 0.1, 999, diffBoardColor, ambiBoardColor, specBoardColor);
            board->resetGrid();
            board->createMenu();
        }

        // Ініціалізація рахунків гри
        unsigned int currentScore = Score::getInstance().getCurrentScore();
        Score::getInstance().readRecordFromFile();
        if (currentScore > Score::getInstance().getRecordScore())
        {
            Score::getInstance().setRecordScore(currentScore);
        }
        if (currentScore > 0)
        {
            Score::getInstance().setPreviousScore(currentScore);
            Score::getInstance().setCurrentScore(0);
        }
    }

    // Пошук куба, найближчого до позиції курсору миші
    bool Scene::findNearest(int x, int y, int &x1, int &z1)
    {
        int viewport[4];
        int iMin = -1, jMin = -1;
        double mvMatrix[16], projMatrix[16];
        double minDist = 8000;

        for (int i = 0; i < M; i++)
        {
            for (int j = 0; j < N; j++)
            {
                if (board->grid[i][j])
                {
                    double wx = board->grid[i][j]->getXCenter();
                    double wy = board->grid[i][j]->getYCenter();
                    double wz = board->grid[i][j]->getZCenter();

                    // Заповнення масиву viewport поточною областю перегляду
                    glGetIntegerv(GL_VIEWPORT, viewport);

                    // Заповнення масиву поточними матрицями
                    glGetDoublev(GL_MODELVIEW_MATRIX, mvMatrix);
                    glGetDoublev(GL_PROJECTION_MATRIX, projMatrix);

                    // Світові x, y, z координати, що обертаються
                    double dx, dy, dz;

                    // Отримання координат точки, на яку спроектовано поточний куб
                    gluProject(wx, wy, wz, mvMatrix, projMatrix, viewport, &dx, &dy, &dz);
                    dy = viewport[3] - dy - 1;
                    double d = (x - dx) * (x - dx) + (y - dy) * (y - dy);
                    if (d < minDist)
                    {
                        minDist = d;
                        iMin = i;
                        jMin = j;
                    }
                }
            }
        }

        // знайдено найближчий куб
        if (minDist < 7000)
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

    // Перемога в грі
    void Scene::on_lose()
    {
        gameState = -1;
    }

    // Поразка в грі
    void Scene::on_win()
    {
        gameState = 1;
    }

    // Вибір елементу розмірів поля в меню
    void Scene::on_menu(int selection_id)
    {
        switch (selection_id)
        {
        case 0:
            M = 4;
            N = 4;
            break;
        case 1:
            M = 5;
            N = 5;
            break;
        case 2:
            M = 6;
            N = 6;
            break;
        default:
            std::cout << "**[WARNING]** Wrong selection_id for on_menu() !" << std::endl;
            break;
        }
        gameState = 0;
        initialize();
    }

    // Оброблювач події, пов'язаної з перемалюванням вікна
    void Scene::on_paint()
    {
        // Масиви для зберігання головної інформації гри та рахунків
        char textInfo[128];
        char textCurrentScore[128];
        char textPreviousScore[128];
        char textRecordScore[128];

        // Заповнення масиву символів відповідно до стану гри
        switch (gameState)
        {
        case -1:
            sprintf(textInfo, "YOU LOST.        TIME: %d sec.       F2 - RESTART GAME       ESC - EXIT", time);
            break;
        case 0:
            sprintf(textInfo, "TIME: %d sec.        F2 - RESTART GAME       ESC - EXIT", time);
            break;
        case 1:
            sprintf(textInfo, "YOU WON.        TIME: %d sec.        F2 - RESTART GAME       ESC - EXIT", time);
            break;
        case 2:
            sprintf(textInfo, " ");
            break;
        }

        // Заповнення масивів символів рахунків, якщо гравець знаходиться не у меню
        if (gameState != 2)
        {
            sprintf(textCurrentScore, "Current score: %d", Score::getInstance().getCurrentScore());
            sprintf(textPreviousScore, "Previous score: %d", Score::getInstance().getPreviousScore());
            sprintf(textRecordScore, "Record score: %d", Score::getInstance().getRecordScore());
        }

        glViewport(0, 0, width, height);

        float lightAmbient[] = {0.0f, 0.0f, 0.0f, 1.0f};
        float lightDiffuse[] = {1.0f, 1.0f, 1.0f, 1.0f};
        float lightSpecular[] = {1.0f, 1.0f, 1.0f, 1.0f};
        float lightPosition[] = {-1.0f, 2.0f, 1.9f, 0.0f};

        // Встановлення параметрів джерела світла
        glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmbient);
        glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiffuse);
        glLightfv(GL_LIGHT0, GL_SPECULAR, lightSpecular);
        glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);

        // Встановлення коліру заднього фону в залежності від стану гри
        switch (gameState)
        {
        case -1:
            glClearColor(0.97, 0.84, 0.88, 0);
            break;
        case 0:
            glClearColor(0.98, 0.92, 0.94, 0);
            break;
        case 1:
            glClearColor(0.94, 0.98, 0.92, 0);
            break;
        case 2:
            glClearColor(0.98, 0.92, 0.94, 0);
            break;
        }

        // Очищення буфери
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glPushMatrix();
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();

        // Відображення тексту з використанням ортографічної проекції
        glOrtho(0, 1, 0, 1, -1, 1);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

        // Встановлення коліру тексту для першої строки інформації на екрані
        switch (gameState)
        {
        case -1:
            glColor3d(0.91, 0.35, 0.21);
            break;
        case 0:
            glColor3f(0.28, 0.25, 0.28);
            break;
        case 1:
            glColor3d(0.004, 0.58, 0.05);
            break;
        }

        // Встановлення чорного коліру тексту для строк рахунку
        if (gameState != 2)
        {
            drawString(GLUT_BITMAP_HELVETICA_18, textInfo, 0.01, 0.965);

            glColor3f(0.28, 0.25, 0.28);

            drawString(GLUT_BITMAP_HELVETICA_18, textCurrentScore, 0.01, 0.915);
            drawString(GLUT_BITMAP_HELVETICA_18, textPreviousScore, 0.01, 0.89);
            drawString(GLUT_BITMAP_HELVETICA_18, textRecordScore, 0.01, 0.865);
        }
        glPopMatrix();

        // Включення режиму роботи з матрицею проекцій:
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();

        // Задання усіченого конуса видимості в лівосторонній системі координат
        gluPerspective(60, width / height, 1, 100);

        // Включення режим роботи з видовою матрицею
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        glTranslatef(0, 0, distZ);

        glRotatef(angleX, 0.0f, 1.0f, 0.0f);
        glRotatef(angleY, 1.0f, 0.0f, 0.0f);
        
        // Включення буферу глибини, режиму установки освітлення 
        // та додавання джерела світла №0
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_LIGHTING);
        glEnable(GL_LIGHT0);

        // Малюємо дошку з усіма кубами
        board->draw();

        // Вимикання усього, що включили:
        glDisable(GL_LIGHT0);
        glDisable(GL_LIGHTING);
        glDisable(GL_DEPTH_TEST);

        glFlush();
        glutSwapBuffers();
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
        // Зберігання поточних координат миші
        mouseX = x;
        mouseY = y;

        this->button = button;

        // Виклик функції on_menu в залежності від найближчого куба
        if (gameState == 2)
        {
            if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
            {
                int x1, z1;
                findNearest(x, y, x1, z1);

                switch (z1)
                {
                    case 0:
                        on_menu(0);
                        break;
                    case 1:
                        on_menu(1);
                        break;
                    case 2:
                        on_menu(2);
                        break;
                    default:
                        break;
                }
            }
        }
    }

    // Оброблювач подій, пов'язаних з пересуванням миші з натисненою кнопкою
    void Scene::on_motion(int x, int y)
    {
        switch (button)
        {
        // обертання сцени правою кнопкою миші
        case 2: 
            if (gameState == 2)
                return;
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
        switch (key)
        {
        // наближення камери
        case GLUT_KEY_UP: 
            if (distZ > -1.5)
            {
                break;
            }
            distZ += 0.1;
            break;
        // віддалення камери 
        case GLUT_KEY_DOWN:
            if (distZ < -2.3)
            {
                break;
            }
            distZ -= 0.1;
            break;
        // нова гра
        case GLUT_KEY_F2:
            gameState = 0;
            initialize();
            break;
        }
    }

    // Обробка подій від клавіатури:
    void Scene::on_keyboard(unsigned char key, int x, int y)
    {
        int res;
        switch (key)
        {
        // Рух кубів догори при натисканні клавиш 'W' або 'w'
        case 'W':
        case 'w':
            if (gameState != 0) break;

            res = board->moveCubes(MOVE_CUBES_UP);
            if (res < 0)
            {
                on_lose();
            }
            else if (res > 0)
            {
                on_win();
            }
            break;
        // Рух кубів донизу при натисканні клавиш 'S' або 's'
        case 'S':
        case 's':
            if (gameState != 0) break;

            res = board->moveCubes(MOVE_CUBES_DOWN);
            if (res < 0)
            {
                on_lose();
            }
            else if (res > 0)
            {
                on_win();
            }
            break;
        // Рух кубів вліво при натисканні клавиш 'A' або 'a'
        case 'A':
        case 'a':
            if (gameState != 0) break;

            res = board->moveCubes(MOVE_CUBES_LEFT);
            if (res < 0)
            {
                on_lose();
            }
            else if (res > 0)
            {
                on_win();
            }
            break;
        // Рух кубів вправо при натисканні клавиш 'D' або 'd'
        case 'D':
        case 'd':
            if (gameState != 0) break;

            res = board->moveCubes(MOVE_CUBES_RIGHT);
            if (res < 0)
            {
                on_lose();
            }
            else if (res > 0)
            {
                on_win();
            }
            break;
        // Завершення гри при натисканні 'ESC'
        case 27:
            exit(0);
            break;

        default:
            break;
        }
    }

    int tick = 0; // лічильник, значення якого змінюється кожні 10 мс

    // Оброблювач події від таймера
    void Scene::on_timer(int value)
    {
        tick++;
        // наступна секунда
        if (tick >= 40)
        {
            if (gameState == 0)
            {
                time++;
            }
            tick = 0;
        }
        // перемалювання вікна
        on_paint();
    }

}