#include "Board.h"

namespace Game
{

    Board::Board(float xCenter, float yCenter, float zCenter,
            float xSize, float ySize, float zSize,
            float *diffColor, float *ambiColor, float *specColor)
            : Shape(xCenter, yCenter, zCenter,
                xSize, ySize, zSize,
                specColor, diffColor, ambiColor) 
    { 
        // Заповнюємо grid з nullptr
        grid.resize(N, std::vector<std::shared_ptr<Cube>>(M, nullptr));

        // Ініціалізуємо генератор випадкових чисел
        std::srand(std::time(NULL));
    }

    void Board::createMenu()
    {
        grid[0][1] = std::make_shared<Cube>(allocX(0), 0.15, allocZ(1), 0.2, 0.2, 0.2, 0, 1, "4x4");
        grid[1][1] = std::make_shared<Cube>(allocX(1), 0.15, allocZ(1), 0.2, 0.2, 0.2, 1, 1, "5x5");
        grid[2][1] = std::make_shared<Cube>(allocX(2), 0.15, allocZ(1), 0.2, 0.2, 0.2, 2, 1, "6x6");
    }

    // !
    
    void Board::addRandomCube()
    {
        std::vector<std::pair<int, int>> emptyPositions;

        // Шукаємо пусті позиції у сітці кубів
        for (int i = 0; i < N; ++i)
        {
            for (int j = 0; j < M; ++j)
            {
                if (!grid[i][j]) 
                {
                    emptyPositions.push_back({i, j});
                }
            }
        }

        // Завершуємо виконання функції, якщо вільних місць немає
        if(emptyPositions.empty()) return;

        // Створюємо два куба з випадковим значення value(2 або 4)
        // та розташовуємо їх у випадкових позиціях
        int randIndex = std::rand() % emptyPositions.size();
        int row = emptyPositions[randIndex].first;
        int col = emptyPositions[randIndex].second;

        if (!grid[row][col])
        {
            int value = (std::rand() % 2 + 1) * 2;
            grid[row][col] = std::make_shared<Cube>(allocX(col), 0.15, allocZ(row), 0.2, 0.2, 0.2, row, col, std::to_string(value));
        }
        //grid[row][col] = newCube;
        //     board->grid[cube_x][cube_y] = new Cube(allocX(j), 0.15, allocZ(i), 0.2, 0.2, 0.2, diffCubeColor1, ambiCubeColor1, specCubeColor1, 1024);
    } 

    /*void Board::addRandomCube()
    {
        std::vector<std::pair<int, int>> emptyCells;

        // Find all empty cells and store their indices
        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < M; j++)
            {
                if (!grid[i][j])
                {
                    emptyCells.emplace_back(i, j);
                }
            }
        }

        // If there are empty cells, add a new cube to a random empty cell
        if (!emptyCells.empty())
        {
            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_int_distribution<> dist(0, emptyCells.size() - 1);

            int randomIndex = dist(gen);
            int randomI = emptyCells[randomIndex].first;
            int randomJ = emptyCells[randomIndex].second;

            int value = ((rand() % 2) + 1) * 2;
            grid[randomI][randomJ] = std::make_shared<Cube>(allocX(randomJ), 0.15, allocZ(randomI), 0.2, 0.2, 0.2, randomJ, randomI, value);
        }
    }*/

    // Рухає куби у заданому напрямку
    // повертає -1, якщо куби не можуть рухатись
    // повертає 0, якщо куби можуть рухатись
    // повертає 1, якщо на полі є куб зі значенням 2048
    int Board::moveCubes(int direction)
    {
        bool isCube2048 = false;
        
        // Двигаємо куби в залежності від змінной direction
        switch (direction)
        {
        case MOVE_CUBES_UP:
            // Проходження по стовпчиках зліва направо
            for (int j = 0; j < M; j++)
            {
                // Рухаємо куби вгору
                for (int i = 1; i < N; i++)
                {
                    int target = i;
                    while (target > 0 && !grid[target - 1][j])
                    {
                        if (grid[target][j]) // Перевіряємо чи є куб 
                        {
                            grid[target - 1][j] = std::move(grid[target][j]);
                            grid[target - 1][j]->setPosition(allocX(j), 0.15, allocZ(target - 1));
                            grid[target - 1][j]->setGridCoords(target - 1, j);
                            grid[target][j] = nullptr;
                        }
                        target--;
                        //moved = true;
                    }
                }

                // Об'єднуємо куби з однаковими значеннями
                for (int i = 0; i < N - 1; i++)
                {
                    if (grid[i][j] && grid[i + 1][j] && !grid[i][j]->isMerged() && grid[i][j]->getValue() == grid[i + 1][j]->getValue())
                    {
                        mergeCubes(grid[i + 1][j], grid[i][j], &isCube2048);
                        grid[i + 1][j] = nullptr;
                        //moved = true;
                    }
                }

                // Рухаємо куби вгору знову для заповнення пустих клітинок після злиття
                for (int i = 1; i < N; i++)
                {
                    int target = i;
                    while (target > 0 && !grid[target - 1][j])
                    {
                        if (grid[target][j]) // Перевіряємо чи є куб 
                        {
                            grid[target - 1][j] = std::move(grid[target][j]);
                            grid[target - 1][j]->setPosition(allocX(j), 0.15, allocZ(target - 1));
                            grid[target - 1][j]->setGridCoords(target - 1, j);
                            grid[target][j] = nullptr;
                        }
                        target--;
                        //moved = true;
                    }
                }
            }
            break;
        case MOVE_CUBES_DOWN:
            // Проходження по стовпчиках зліва направо
            for (int j = 0; j < M; j++)
            {
                // Рухаємо куби вниз
                for (int i = N - 2; i >= 0; i--)
                {
                    int target = i;
                    while (target < N - 1 && !grid[target + 1][j])
                    {
                        if (grid[target][j]) // Перевіряємо чи є куб 
                        {
                            grid[target + 1][j] = std::move(grid[target][j]);
                            grid[target + 1][j]->setPosition(allocX(j), 0.15, allocZ(target + 1));
                            grid[target + 1][j]->setGridCoords(target + 1, j);
                            grid[target][j] = nullptr;
                        }
                        target++;
                        //moved = true;
                    }
                }

                // Об'єднуємо куби з однаковими значеннями
                for (int i = N - 1; i > 0; i--)
                {
                    if (grid[i][j] && grid[i - 1][j] && !grid[i][j]->isMerged() && grid[i][j]->getValue() == grid[i - 1][j]->getValue())
                    {
                        mergeCubes(grid[i - 1][j], grid[i][j], &isCube2048);
                        grid[i - 1][j] = nullptr;
                        //moved = true;
                    }
                }

                // Рухаємо куби вниз знову для заповнення пустих клітинок після злиття
                for (int i = N - 2; i >= 0; i--)
                {
                    int target = i;
                    while (target < N - 1 && !grid[target + 1][j])
                    {
                        if (grid[target][j]) // Перевіряємо чи є куб 
                        {
                            grid[target + 1][j] = std::move(grid[target][j]);
                            grid[target + 1][j]->setPosition(allocX(j), 0.15, allocZ(target + 1));
                            grid[target + 1][j]->setGridCoords(target + 1, j);
                            grid[target][j] = nullptr;
                        }
                        target++;
                        //moved = true;
                    }
                }
            }
            break;
        case MOVE_CUBES_LEFT:
            // Проходження по рядках зверху вниз
            for (int i = 0; i < N; i++)
            {
                // Рухаємо куби вліво
                for (int j = 1; j < M; j++)
                {
                    int target = j;
                    while (target > 0 && !grid[i][target - 1])
                    {
                        if (grid[i][target]) // Перевіряємо чи є куб 
                        {
                            grid[i][target - 1] = std::move(grid[i][target]);
                            grid[i][target - 1]->setPosition(allocX(target - 1), 0.15, allocZ(i));
                            grid[i][target - 1]->setGridCoords(i, target - 1);
                            grid[i][target] = nullptr;
                        }
                        target--;
                        //moved = true;
                    }
                }

                // Об'єднуємо куби з однаковими значеннями
                for (int j = 0; j < M - 1; j++)
                {
                    if (grid[i][j] && grid[i][j + 1] && !grid[i][j]->isMerged() && grid[i][j]->getValue() == grid[i][j + 1]->getValue())
                    {
                        mergeCubes(grid[i][j + 1], grid[i][j], &isCube2048);
                        grid[i][j + 1] = nullptr;
                        //moved = true;
                    }
                }

                // Рухаємо куби вліво знову для заповнення пустих клітинок після злиття
                for (int j = 1; j < M; j++)
                {
                    int target = j;
                    while (target > 0 && !grid[i][target - 1])
                    {
                        if (grid[i][target]) // Перевіряємо чи є куб 
                        {
                            grid[i][target - 1] = std::move(grid[i][target]);
                            grid[i][target - 1]->setPosition(allocX(target - 1), 0.15, allocZ(i));
                            grid[i][target - 1]->setGridCoords(i, target - 1);
                            grid[i][target] = nullptr;
                        }
                        target--;
                        //moved = true;
                    }
                }
            }
            break;
        case MOVE_CUBES_RIGHT:
            // Проходження по рядках зверху вниз
            for (int i = 0; i < N; i++)
            {
                // Рухаємо куби вправо
                for (int j = M - 2; j >= 0; j--)
                {
                    int target = j;
                    while (target < M - 1 && !grid[i][target + 1])
                    {
                        if (grid[i][target]) // Перевіряємо чи є куб 
                        {
                            grid[i][target + 1] = std::move(grid[i][target]);
                            grid[i][target + 1]->setPosition(allocX(target + 1), 0.15, allocZ(i));
                            grid[i][target + 1]->setGridCoords(i, target + 1);
                            grid[i][target] = nullptr;
                        }
                        target++;
                        //moved = true;
                    }
                }

                // Об'єднуємо куби з однаковими значеннями
                for (int j = M - 1; j > 0; j--)
                {
                    if (grid[i][j] && grid[i][j - 1] && !grid[i][j]->isMerged() && grid[i][j]->getValue() == grid[i][j - 1]->getValue())
                    {
                        mergeCubes(grid[i][j - 1], grid[i][j], &isCube2048);
                        grid[i][j - 1] = nullptr;
                        //moved = true;
                    }
                }

                // Рухаємо куби вправо знову для заповнення пустих клітинок після злиття
                for (int j = M - 2; j >= 0; j--)
                {
                    int target = j;
                    while (target < M - 1 && !grid[i][target + 1])
                    {
                        if (grid[i][target]) // Перевіряємо чи є куб 
                        {
                            grid[i][target + 1] = std::move(grid[i][target]);
                            grid[i][target + 1]->setPosition(allocX(target + 1), 0.15, allocZ(i));
                            grid[i][target + 1]->setGridCoords(i, target + 1);
                            grid[i][target] = nullptr;
                        }
                        target++;
                        //moved = true;
                    }
                }
            }
            break;       
        default:
            std::cout << "*[WARNING]* Function Board.cpp::moveCubes() has been given wrong direction!" << std::endl;
            break;
        }

        // Оновлюємо позиції кожного куба на полі
        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < M; j++)
            {
                if (grid[i][j])
                {
                    grid[i][j]->setPosition(allocX(j), 0.15, allocZ(i));
                }
            }
        }

        addRandomCube();

        // Ставимо флаг false для усіх кубів
        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < M; j++)
            {
                if (grid[i][j])
                {
                    grid[i][j]->setMerged(false);
                }
            }
        }

        if (!hasAvailableMoves())
            return -1;

        // ! 
        /*if (!moved)
        {
            std::cout << "Not moved" << std::endl;
            return -1;
        }*/
        
        if (isCube2048)
            return 1;

        //printGrid();
        return 0;
    }

    //Глобальний map для зберігання лямбда-функцій з унікальними ідентифікаторами
    std::map<int, std::function<void(int)>> g_timerFunctions;

    //Глобальна змінна для зберігання унікального ідентифікатора лямбда-функцій
    int g_timerFunctionId = 0;


    void timerCallback(int timerId)
    {
        if (g_timerFunctions.count(timerId) > 0)
        {
            g_timerFunctions[timerId](timerId);
            g_timerFunctions.erase(timerId); // Видалити лямбда-функцію після виконання
        }
    }

    // !
    void Board::mergeCubes(std::shared_ptr<Cube>& cube1, std::shared_ptr<Cube>& cube2, bool* isValue2048)
    {
        try
        {
            int oldValue = std::stoi(cube2->getValue());
            int newValue = oldValue * 2;

            cube2->setValue(std::to_string(newValue)); // Подвоєння значення куба cube2
            cube2->setPosition(cube1->getXCenter(), cube1->getYCenter(), cube1->getZCenter()); // Оновлення позиції куба2 відповідно до позиції куба1
            //std::cout << "Cube2 pos X: " << cube2->getGridX() << " Z: " << cube2->getGridZ() << std::endl;
            cube2->setMerged(true); // Встановлення статусу злиття куба cube2 в true
            Score::addCurrentScore(newValue);

            float originalScale = 0.2f;
            float scaleFactor = 1.15f;
            cube2->setSize(originalScale * scaleFactor, originalScale * scaleFactor, originalScale * scaleFactor);

            int currentTimerId = g_timerFunctionId++;
            g_timerFunctions[currentTimerId] = [cube2, originalScale](int value) {
                cube2->setSize(originalScale, originalScale, originalScale);
            };
            glutTimerFunc(175, timerCallback, currentTimerId);

            cube1.reset(); // Видалення cube1 з поля гри

            if (cube2->getValue() == "2048")
            {
                *isValue2048 = true;
            }
        }
        catch(const std::invalid_argument& ia)
        {
            std::cerr << "Could not convert the cube value to an integer: " << ia.what() << std::endl;
        }
    }


    bool Board::hasAvailableMoves()
    {
        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < M; j++)
            {
                // Перевіряємо наявність пустих місць у сітці дошки
                if (!grid[i][j]) 
                {
                    return true;
                }

                // Перевіряємо можливість "з'єднання" кубів 
                // з однаковими значеннями по горизонталі
                if (j < M - 1 && grid[i][j] && grid[i][j + 1] && grid[i][j]->getValue() == grid[i][j + 1]->getValue())
                {
                    return true;
                }

                // Перевіряємо можливість "з'єднання" кубів 
                // з однаковими значеннями по вертикалі
                if (i < N - 1 && grid[i][j] && grid[i + 1][j] && grid[i][j]->getValue() == grid[i + 1][j]->getValue())
                {
                    return true;
                }
            }
        }
        return false;
    }

    void Board::resetGrid()
    {
        for (size_t i = 0; i < grid.size(); ++i) 
        {
            for (size_t j = 0; j < grid[i].size(); ++j) 
            {
                grid[i][j] = nullptr;
            }
        }
    }

    void Board::printGrid()
    {
        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < M; j++)
            {
                if (grid[i][j])
                {
                    std::cout << grid[i][j]->getValue() << " ";
                }
                else
                {
                    std::cout << "0 ";
                }
            }
            std::cout << std::endl;
        }
        std::cout << "-------------------" << std::endl;
    }


    void Board::draw()
    {
        glMaterialfv(GL_FRONT, GL_AMBIENT, getAmbiColor());
        glMaterialfv(GL_FRONT, GL_DIFFUSE, getDiffColor());
        glMaterialfv(GL_FRONT, GL_SPECULAR, getSpecColor());
        glMaterialf(GL_FRONT, GL_SHININESS, shininess);
        // Запис поточної матриці в стек
        // (збереження вмісту поточної матриці для подальшого використання):
        glPushMatrix();
        glTranslatef(getXCenter(), getYCenter(), getZCenter());
        parallelepiped(getXSize(), getYSize(), getZSize());

        // Малюємо усі куби:
        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < M; j++)
            {
                if (grid[i][j])
                {
                    grid[i][j]->draw();
                }
            }
        }

        // Відновлення поточної матриці зі стека:
        glPopMatrix();
    }

}