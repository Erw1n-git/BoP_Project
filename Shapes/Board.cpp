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
            grid[row][col] = std::make_shared<Cube>(allocX(col), 0.15, allocZ(row), 0.2, 0.2, 0.2, row, col, value);
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

    void Board::moveCubes(int direction)
    {
        bool moved = false;
        
        // Двигаємо куби в залежності від змінной direction
        switch (direction)
        {
        case CUBES_MOVE_UP:
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
                            grid[target][j] = nullptr;
                        }
                        target--;
                        moved = true;
                    }
                }

                // Об'єднуємо куби з однаковими значеннями
                for (int i = 0; i < N - 1; i++)
                {
                    if (grid[i][j] && grid[i + 1][j] && !grid[i][j]->isMerged() && grid[i][j]->getTextValue() == grid[i + 1][j]->getTextValue())
                    {
                        mergeCubes(grid[i + 1][j], grid[i][j]);
                        grid[i + 1][j] = nullptr;
                        moved = true;
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
                            grid[target][j] = nullptr;
                        }
                        target--;
                        moved = true;
                    }
                }
            }
            break;       
        default:
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

        printGrid();
    }

    void Board::printGrid()
    {
        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < M; j++)
            {
                if (grid[i][j])
                {
                    std::cout << grid[i][j]->getTextValue() << " ";
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

    void Board::mergeCubes(std::shared_ptr<Cube>& cube1, std::shared_ptr<Cube>& cube2)
    {
        cube2->setTextValue(cube2->getTextValue() * 2); // Подвоєння значення куба cube2
        std::cout << "test 3" << std::endl;
        cube2->setPosition(cube1->getXCenter(), cube1->getYCenter(), cube1->getZCenter()); // Updating cube2's position to match cube1's position
        cube2->setMerged(true); // Встановлення статусу злиття куба cube2 в true
        cube1.reset(); // Видалення cube1 з поля гри
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