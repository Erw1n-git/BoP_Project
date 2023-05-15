#include "Scene.h"

namespace Game
{

    // Параметри конструктора - відстань між окремими кубами:
    Scene::Scene(float xStep, float zStep)
    {
        this->xStep = xStep;
        this->zStep = zStep;

        // Додаємо дошку сірого кольору.
        // Розміри визначаємо так, щоб поміщалися всі стрижні:
        // std::shared_ptr<Board> board = std::make_shared<Board>(0.0, 0.0, 0.0, N * xStep + 0.2, 0.1, M * xStep + 0.2, diffBoardColor, ambiBoardColor, specBoardColor);
        // shapes.push_back(board);

        gameState = 2;

        // boardGame = std::make_shared<Board>(0.0, 0.0, 0.0, N * xStep + 0.2, 0.1, M * xStep + 0.2, diffBoardColor, ambiBoardColor, specBoardColor);
        // boardGame = std::make_shared<Board>(0.0, 0.0, 0.0, 999, 0.1, 999, diffBoardColor, ambiBoardColor, specBoardColor);
        //  !
        // board->addRandomCube();
        // board->addRandomCube();
        // board->printGrid();

        // Генеруємо два випадкових куба
        // std::shared_ptr<Cube> cube1 = board->addRandomCube();
        // std::shared_ptr<Cube> cube2 = board->addRandomCube();

        // shapes.push_back(cube1);
        // shapes.push_back(cube2);

        // ! shapes.push_back(new Board(0.0, 0.0, 0.0, N * xStep + 0.2, 0.1, M * xStep + 0.2, diffBoardColor, ambiBoardColor, specBoardColor));
        // Додаємо стрижні (крім останнього ряду):
        for (int i = 0; i < M; i++)
        {
            // for (int j = 0; j < 2; ++j)
            // {
            //     int cube_x = rand() % 4;
            //     int cube_y = rand() % 4;
            //     int cube_value = rand() % 2 == 0 ? 2 : 4;

            //     board->grid.insert(board->grid.begin() + cube_x, std::vector<Cube*>());

            //     board->grid[cube_x][cube_y] = new Cube(allocX(j), 0.15, allocZ(i), 0.2, 0.2, 0.2, diffCubeColor1, ambiCubeColor1, specCubeColor1, 1024);
            // }

            // !
            /*for (int j = 0; j < N; j++)
            {
                if(j == 0)
                {
                    shapes.push_back(new Cube(allocX(j), 0.15, allocZ(i), 0.2, 0.2, 0.2, diffCubeColor2, ambiCubeColor2, specCubeColor2, 1024));
                }
                else if(j == 1)
                {
                    shapes.push_back(new Cube(allocX(j), 0.15, allocZ(i), 0.2, 0.2, 0.2, diffCubeColor4, ambiCubeColor4, specCubeColor4, 2048));
                }
                else
                {
                    shapes.push_back(new Cube(allocX(j), 0.15, allocZ(i), 0.2, 0.2, 0.2, diffCubeColor4, ambiCubeColor4, specCubeColor4, 512));
                }
            }*/
        }

        // !
        // Додаємо останній ряд стрижнів:
        // shapes.push_back(new Cube(allocX(0), 0.15, allocZ(M - 1), 0.1, 0.1, 0.1, diffRed, ambiRed, specRed, 256));
        // shapes.push_back(new Cube(allocX(1), 0.15, allocZ(M - 1), 0.1, 0.1, 0.1, diffYellow, ambiYellow, specYellow, 256));
        // shapes.push_back(new Cube(allocX(2), 0.15, allocZ(M - 1), 0.1, 0.1, 0.1, diffGreen, ambiGreen, specGreen, 256));
        // !
        // Додаємо диски в першому ряду:
        // shapes.push_back(disks[0] = new Disk(allocX(0), 0.1, allocZ(0), 0.3, 0.1, 0.3, diffRed, ambiRed, specRed, 0.05));
        // shapes.push_back(disks[1] = new Disk(allocX(1), 0.1, allocZ(0), 0.3, 0.1, 0.3, diffYellow, ambiYellow, specYellow, 0.05));
        // shapes.push_back(disks[2] = new Disk(allocX(2), 0.1, allocZ(0), 0.3, 0.1, 0.3, diffGreen, ambiGreen, specGreen, 0.05));

        // Здійснюємо ініціалізацію параметрів перед першою грою:
        initialize();
        //setupMenu();
    }

    // void Scene::setMenu()
    // {
    //     gameState = 2;
    //     initialize();
    // }

    // !
    // Scene::~Scene()
    // {
    //     // Видаляємо всі фігури:
    //     for (int i = 0; i < shapes.size(); i++)
    //     {
    //         delete shapes[i];
    //     }
    // }

    // !
    // // Перерахування індексу масиву fields в координату x
    // float Scene::allocX(int i)
    // {
    //     return xStep * i - (N - 1) * xStep / 2;
    // }

    // // Перерахування індексу масиву fields в координату z
    // float Scene::allocZ(int i)
    // {
    //     return zStep * i - (M - 1) * zStep / 2;
    // }

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
    */
    // !

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
        // distZ = -1.7;
        angleX = 2;
        angleY = 77;
        time = 0;
        // finish = false;
        // ! gameState = 0;
        // gameState = 2;

        // Ініціалізація кубів на полі:
        // boardGame->resetGrid(); // Чистимо поле, на випадок, якщо воно заповнене кубами з минулої спроби
        // std::cout << "gamestate: " << gameState << std::endl;

        // boardGame = std::make_shared<Board>(0.0, 0.0, 0.0, N * xStep + 0.2, 0.1, M * xStep + 0.2, diffBoardColor, ambiBoardColor, specBoardColor);

        if (gameState != 2)
        {
            distZ = -1.7;

            boardGame = std::make_shared<Board>(0.0, 0.0, 0.0, N * xStep + 0.2, 0.1, M * xStep + 0.2, diffBoardColor, ambiBoardColor, specBoardColor);
            boardGame->resetGrid();
            boardGame->addRandomCube();
            boardGame->addRandomCube();
        }
        else
        {
            distZ = -1.3;

            boardGame = std::make_shared<Board>(0.0, 0.0, 0.0, 999, 0.1, 999, diffBoardColor, ambiBoardColor, specBoardColor);
            boardGame->resetGrid();
            boardGame->createMenu();
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

    // Пошук стрижня, найближчого до позиції курсору миші:
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

                // Світові x, y, z поточного стрижня:
                // !
                // double wx = allocX(j);
                // double wy = 0.1;
                // double wz = allocZ(i);

                // if ((i == 0 && j == 1) || (i == 1 && j == 1) || (i == 2 && j == 2))
                if (boardGame->grid[i][j])
                {
                    double wx = boardGame->grid[i][j]->getXCenter();
                    double wy = boardGame->grid[i][j]->getYCenter();
                    double wz = boardGame->grid[i][j]->getZCenter();

                    // Заповнюємо масив viewport поточною областю перегляду:
                    glGetIntegerv(GL_VIEWPORT, viewport);

                    // Заповнюємо масиви поточними матрицями:
                    glGetDoublev(GL_MODELVIEW_MATRIX, mvMatrix);
                    glGetDoublev(GL_PROJECTION_MATRIX, projMatrix);

                    // Світові x, y, z координати, що обертаються:
                    double dx, dy, dz;

                    // Отримуємо координати точки, на яку спроектовано поточний стрижень:
                    gluProject(wx, wy, wz, mvMatrix, projMatrix, viewport, &dx, &dy, &dz);
                    dy = viewport[3] - dy - 1;                            // dy необхідно перерахувати
                    double d = (x - dx) * (x - dx) + (y - dy) * (y - dy); // квадрат відстані
                    if (d < minDist)                                      // знайшли ближчий стрижень
                    {
                        minDist = d;
                        iMin = i;
                        jMin = j;
                    }
                }
            }
        }
        if (minDist < 7000) // знайшли найближчий стрижень
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
        // ! finish = true;
        gameState = -1;
    }

    // Поразка в грі
    void Scene::on_win()
    {
        // ! finish = true;
        gameState = 1;
    }

    void Scene::on_menu(int selection_id)
    {
        // N = 4;
        // M = 4;
        // boardGame->resetGrid();
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
        // TODO: Remove variables for scores (if they're used only once)
        unsigned int currentScore = Score::getInstance().getCurrentScore();
        unsigned int previousScore = Score::getInstance().getPreviousScore();
        unsigned int recordScore = Score::getInstance().getRecordScore();

        // Score::getInstance().setRecordScore(1);

        char textInfo[128];          // Масив символів першої строки
        char textCurrentScore[128];  // Масив символів строки поточного рахунку
        char textPreviousScore[128]; // Масив символів строки рахунку минулої гри
        char textRecordScore[128];   // Масив символів строки рекордного рахунку

        // Заповнення масиву символів відповідно до стану гри:

        // !
        // if (finish)
        // {
        //     sprintf(text, "GAME OVER.       TIME: %d SEC.       F2 - RESTART GAME       ESC - EXIT", time);
        // }
        // else
        // {
        //     sprintf(text, "F2 - RESTART GAME        ESC - EXIT      TIME: %d SEC.", time);
        // }

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

        // Заповнення масиву символів рахунків гри
        // sprintf(textScore, "CURRENT SCORE: %d        PREVIOUS SCORE: %d        RECORD SCORE: %d",
        //        currentScore, previousScore, recordScore);

        if (gameState != 2)
        {
            sprintf(textCurrentScore, "Current score: %d", currentScore);
            sprintf(textPreviousScore, "Previous score: %d", previousScore);
            sprintf(textRecordScore, "Record score: %d", recordScore);
        }

        // Встановлюємо область перегляду таку, щоб вона вміщувала все вікно:
        glViewport(0, 0, width, height);

        // Ініціалізуємо параметри матеріалів і джерела світла:
        float lightAmbient[] = {0.0f, 0.0f, 0.0f, 1.0f};  // колір фонового освітлення
        float lightDiffuse[] = {1.0f, 1.0f, 1.0f, 1.0f};  // колір дифузного освітлення
        float lightSpecular[] = {1.0f, 1.0f, 1.0f, 1.0f}; // колір дзеркального відображення
        // ! float lightPosition[] = { 0.0f, 1.0f, 1.0f, 0.0f };// розташування джерела світла
        float lightPosition[] = {-1.0f, 2.0f, 1.9f, 0.0f}; // розташування джерела світла

        // Встановлюємо параметри джерела світла:
        glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmbient);
        glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiffuse);
        glLightfv(GL_LIGHT0, GL_SPECULAR, lightSpecular);
        glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);

        // Визначаємо блакитний колір для очищення:
        // ! if (finish)
        // if (gameState != 0)
        // {
        //     glClearColor(0, 0.7, 0.7, 0);
        //     // ! glClearColor(0.98, 0.92, 0.94, 0);
        // }
        // else
        // {
        //     glClearColor(0, 0.5, 0.5, 0);
        //     // ! glClearColor(0.98, 0.92, 0.94, 0);
        // }

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

        // Очищуємо буфери:
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glPushMatrix();
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();

        // Для відображення тексту, краще використовувати ортографічну проекцію:
        glOrtho(0, 1, 0, 1, -1, 1);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        //!
        // glColor3d(1, 1, 0); // жовтий текст
        // glColor3f(0.278, 0.251, 0.227); // жовтий текст
        switch (gameState)
        {
        case -1:
            glColor3d(0.91, 0.35, 0.21); // Червоний текст
            break;
        case 0:
            glColor3f(0.28, 0.25, 0.28); // Чорний текст
            break;
        case 1:
            // glColor3f(0.37, 0.85, 0.57);
            glColor3d(0.004, 0.58, 0.05); // Зелений текст
            break;
        }

        if (gameState != 2)
        {
            // !
            // drawString(GLUT_BITMAP_TIMES_ROMAN_24, text, 0.01, 0.95);
            drawString(GLUT_BITMAP_HELVETICA_18, textInfo, 0.01, 0.965);
            // drawString(GLUT_BITMAP_HELVETICA_18, textScore, 0.01, 0.92);

            // Встановлюємо чорний текст для строк рахунку
            glColor3f(0.28, 0.25, 0.28);

            drawString(GLUT_BITMAP_HELVETICA_18, textCurrentScore, 0.01, 0.915);
            drawString(GLUT_BITMAP_HELVETICA_18, textPreviousScore, 0.01, 0.89);
            drawString(GLUT_BITMAP_HELVETICA_18, textRecordScore, 0.01, 0.865);
        }
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
        glTranslatef(0, 0, distZ); // камера з початку координат зсувається на distZ,

        glRotatef(angleX, 0.0f, 1.0f, 0.0f); // потім обертається по осі Oy
        glRotatef(angleY, 1.0f, 0.0f, 0.0f); // потім обертається по осі Ox
        glEnable(GL_DEPTH_TEST);             // включаємо буфер глибини (для відсікання невидимих частин зображення)

        // Включаємо режим для установки освітлення:
        glEnable(GL_LIGHTING);

        // Додаємо джерело світла № 0 (їх може бути до 8), зараз воно світить з "очей":
        glEnable(GL_LIGHT0);

        // !
        // Малюємо усі фігури:
        // for (int i = 0; i < shapes.size(); i++)
        // {
        //     shapes[i]->draw();
        // }

        // Малюємо дошку з усіма кубами
        boardGame->draw();

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
        this->button = button; // зберігаємо інформацію про кнопки
        // ! if (finish)
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

                /*if (found)
                {
                    std::cout << "Clicked on the cube at coord(" 
                            << x1 << ", " << z1 << ")" << std::endl;    
                }
                else
                {
                    std::cout << "No cube found near cursor." << std::endl;
                }*/
            }
            else if ((state == GLUT_UP))
            {

            }
        }
        // if (gameState != 0)
        // {
        //     return;
        // }
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
        case GLUT_KEY_UP: // наближення
            // ! if (distZ > -1.7)
            if (distZ > -1.5)
            {
                break;
            }
            distZ += 0.1;
            break;
        case GLUT_KEY_DOWN: // віддалення
            if (distZ < -2.3)
            {
                break;
            }
            distZ -= 0.1;
            break;
        case GLUT_KEY_F2: // нова гра
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
        // Рухаємо куби догори при натисканні клавиш 'W' або 'w'
        case 'W':
        case 'w':
            // ! if (finish) break; // Виходимо з тіла кейсу, якщо гру завершено
            if (gameState != 0)
                break;
            res = boardGame->moveCubes(MOVE_CUBES_UP);
            if (res < 0)
            {
                on_lose();
            }
            else if (res > 0)
            {
                on_win();
            }
            break;
        // Рухаємо куби донизу при натисканні клавиш 'S' або 's'
        case 'S':
        case 's':
            // ! if (finish) break; // Виходимо з тіла кейсу, якщо гру завершено
            if (gameState != 0)
                break;
            res = boardGame->moveCubes(MOVE_CUBES_DOWN);
            if (res < 0)
            {
                on_lose();
            }
            else if (res > 0)
            {
                on_win();
            }
            break;
        // Рухаємо куби вліво при натисканні клавиш 'A' або 'a'
        case 'A':
        case 'a':
            // ! if (finish) break; // Виходимо з тіла кейсу, якщо гру завершено
            if (gameState != 0)
                break;
            res = boardGame->moveCubes(MOVE_CUBES_LEFT);
            if (res < 0)
            {
                on_lose();
            }
            else if (res > 0)
            {
                on_win();
            }
            break;
        // Рухаємо куби вправо при натисканні клавиш 'D' або 'd'
        case 'D':
        case 'd':
            // ! if (finish) break; // Виходимо з тіла кейсу, якщо гру завершено
            if (gameState != 0)
                break;
            res = boardGame->moveCubes(MOVE_CUBES_RIGHT);
            if (res < 0)
            {
                on_lose();
            }
            else if (res > 0)
            {
                on_win();
            }
            break;
        case 27:
            exit(0);
            break;

        default:
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
            // ! if (!finish)// секунди нарощуються, якщо гру не закінчено
            if (gameState == 0)
            {
                time++;
            }
            tick = 0; // скинули лічильник
        }
        on_paint(); // здійснюємо перемалювання вікна
    }

}