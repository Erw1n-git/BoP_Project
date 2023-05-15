#include "Utils.h"

namespace GraphUtils
{
    // Кількість рядків поля гри
    int N = 3;

    // Кількість стовпців поля гри
    int M = 3;

    // Визначення кольорів:
    float diffBoardColor[] = { 0.73f, 0.68f, 0.62f };
    float ambiBoardColor[] = { 0.65f, 0.6f, 0.55f };
    float specBoardColor[] = { 0.81f, 0.75f, 0.7f };

    float diffCubeColor2[] = { 0.93f, 0.89f, 0.85f };
    float ambiCubeColor2[] = { 0.8f, 0.8f, 0.8f };
    float specCubeColor2[] = { 0.9f, 0.9f, 0.9f };

    float diffCubeColor4[] = { 0.925f, 0.878f, 0.784f };
    float specCubeColor4[] = { 0.992f, 0.964f, 0.890f };
    float ambiCubeColor4[] = { 0.925f, 0.878f, 0.784f };

    float diffCubeColor8[] = { 0.95f, 0.7f, 0.47f };
    float specCubeColor8[] = { 0.8f, 0.8f, 0.8f };
    float ambiCubeColor8[] = { 0.47f, 0.44f, 0.4f };

    float diffCubeColor16[] = { 0.92f, 0.55f, 0.32f };
    float specCubeColor16[] = { 0.99f, 0.80f, 0.63f };
    float ambiCubeColor16[] = { 0.74f, 0.44f, 0.25f };

    float diffCubeColor32[] = { 0.96f, 0.48f, 0.37f };
    float specCubeColor32[] = { 0.8f, 0.8f, 0.8f };
    float ambiCubeColor32[] = { 0.49f, 0.28f, 0.25f };

    float diffCubeColor64[] = { 0.91f, 0.35f, 0.21f };
    float specCubeColor64[] = { 0.9f, 0.9f, 0.9f };
    float ambiCubeColor64[] = { 0.45f, 0.18f, 0.11f };

    float diffCubeColor128[] = { 0.92f, 0.8f, 0.44f };
    float specCubeColor128[] = { 1.0f, 1.0f, 1.0f };
    float ambiCubeColor128[] = { 0.92f, 0.8f, 0.44f };

    float diffCubeColor256[] = { 0.95f, 0.82f, 0.29f };
    float specCubeColor256[] = { 1.0f, 0.93f, 0.55f };
    float ambiCubeColor256[] = { 0.96f, 0.81f, 0.16f };

    float diffCubeColor512[] = { 1.0f, 0.72f, 0.0f };
    float specCubeColor512[] = { 1.0f, 0.72f, 0.0f };
    float ambiCubeColor512[] = { 1.0f, 0.72f, 0.0f };

    float diffCubeColor1024[] = { 1.0f, 0.58f, 0.0f };
    float specCubeColor1024[] = { 1.0f, 1.0f, 1.0f };
    float ambiCubeColor1024[] = { 1.0f, 0.58f, 0.0f };

    float diffCubeColor2048[] = { 0.37f, 0.85f, 0.57f };
    float specCubeColor2048[] = { 0.8f, 0.8f, 0.8f };
    float ambiCubeColor2048[] = { 0.2f, 0.2f, 0.2f };

    float diffWhite[] = { 1.0f, 1.0f, 1.0f };
    float ambiWhite[] = { 0.8f, 0.8f, 0.8f };
    float specWhite[] = { 1.0f, 1.0f, 1.0f };

    float diffBlue[] = { 0.0f, 0.0f, 0.6f };
    float ambiBlue[] = { 0.1f, 0.1f, 0.2f };
    float specBlue[] = { 0.2f, 0.2f, 0.8f };

    float diffGray[] = { 0.6f, 0.6f, 0.6f };
    float ambiGray[] = { 0.2f, 0.2f, 0.2f };
    float specGray[] = { 0.8f, 0.8f, 0.8f };

    float diffRed[] = { 0.6f, 0.0f, 0.0f };
    float ambiRed[] = { 0.2f, 0.1f, 0.1f };
    float specRed[] = { 0.8f, 0.2f, 0.2f };

    float diffYellow[] = { 0.9f, 0.9f, 0 };
    float ambiYellow[] = { 0.2f, 0.2f, 0.1f };
    float specYellow[] = { 1.0f, 1.0f, 0.2f };

    float diffGreen[] = { 0, 0.5f, 0 };
    float ambiGreen[] = { 0.1f, 0.2f, 0.1f };
    float specGreen[] = { 0.2f, 0.7f, 0.2f };

    float diffOrange[] = { 0.9f, 0.2f, 0 };
    float ambiOrange[] = { 0.2f, 0.2f, 0.2f };
    float specOrange[] = { 0.8f, 0.8f, 0.8f };

    float diffLightBlue[] = { 0, 0.6f, 0.9f };
    float ambiLightBlue[] = { 0.2f, 0.2f, 0.2f };
    float specLightBlue[] = { 0.8f, 0.8f, 0.8f };

    float diffViolet[] = { 0.5f, 0, 0.5f };
    float ambiViolet[] = { 0.2f, 0.2f, 0.2f };
    float specViolet[] = { 0.8f, 0.8f, 0.8f };

    // Перерахування індексу масиву fields в координату x
    float allocX(int i)
    {
        return xStep * i - (N - 1) * xStep / 2;
    }

    // Перерахування індексу масиву fields в координату z
    float allocZ(int i)
    {
        return zStep * i - (M - 1) * zStep / 2;
    }

    // Випадкове "тасування" одновимірного масиву цілих чисел
    void shuffle(int *a, int size)
    {
        // Ініціалізація генератору випадкових значень поточним часом:
        srand((unsigned)time(0));
        std::random_shuffle(a, a + size); // алгоритм стандартної бібліотеки шаблонів
    }

    // Малювання паралелепіпеда
    void parallelepiped(float length, float width, float height)
    {
        glBegin(GL_QUAD_STRIP);
        //грань 1 || YZ, x<0
        glNormal3f(-1.0f, 0.0f, 0.0f);
        glVertex3f(-length / 2, -width / 2, -height / 2);
        glVertex3f(-length / 2, -width / 2, height / 2);
        glVertex3f(-length / 2, width / 2, -height / 2);
        glVertex3f(-length / 2, width / 2, height / 2);

        //грань 2 || ZX, y>0
        glNormal3f(0.0f, 1.0f, 0.0f);
        glVertex3f(length / 2, width / 2, -height / 2);
        glVertex3f(length / 2, width / 2, height / 2);

        //грань 3 || YZ, x>0
        glNormal3f(1.0f, 0.0f, 0.0f);
        glVertex3f(length / 2, -width / 2, -height / 2);
        glVertex3f(length / 2, -width / 2, height / 2);

        //грань 4 || ZX y<0
        glNormal3f(0.0f, -1.0f, 0.0f);
        glVertex3f(-length / 2, -width / 2, -height / 2);
        glVertex3f(-length / 2, -width / 2, height / 2);
        glEnd();

        glBegin(GL_QUADS);
        //грань 5 || YX, z>0
        glNormal3f(0.0f, 0.0f, 1.0f);
        glVertex3f(-length / 2, -width / 2, height / 2);
        glVertex3f(-length / 2, width / 2, height / 2);
        glVertex3f(length / 2, width / 2, height / 2);
        glVertex3f(length / 2, -width / 2, height / 2);

        //грань 6  || YX, z<0
        glNormal3f(0.0f, 0.0f, -1.0f);
        glVertex3f(-length / 2, -width / 2, -height / 2);
        glVertex3f(-length / 2, width / 2, -height / 2);
        glVertex3f(length / 2, width / 2, -height / 2);
        glVertex3f(length / 2, -width / 2, -height / 2);
        glEnd();
    }

    // Відображення рядка тексту вказаним шрифтом у вказаній позиції
    void drawString(void *font, const char* text, float x, float y)
    {
        if (!text) // нульовий указівник
        {
            return;
        }
        // Встановлення позиції тексту:
        glRasterPos2f(x, y);
        while (*text)
        {
            // Рядок виводиться посимвольно:
            glutBitmapCharacter(font, *text);
            text++;
        }
    }
}